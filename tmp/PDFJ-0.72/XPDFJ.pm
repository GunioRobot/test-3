# XPDFJ.pm - PDFJ XML interface
# 2002-3 <nakajima@netstock.co.jp>
package XPDFJ;
use PDFJ qw(UTF8);
use XML::Parser;
#use Data::Dumper;
use Safe;
use Carp;
use strict;
use vars qw($VERSION $bytesimport);

$VERSION = 0.12;

my $VarnamePtn = qr/^\$[A-Za-z_]\w*(\{[A-Za-z_]\w*\})?$/;
my $DebugIndent = "";

if( $] > 5.007 ) {
	require bytes;
	$bytesimport = \&bytes::import;
}

sub new {
	my($class, %args) = @_;
	my $safe = new Safe;
	$safe->permit_only(qw(:default));
	$safe->share(qw(istext addcomma autonl));
	$safe->share(qw($bytesimport)) if $] > 5.007;
	my %Args;
	my $ArgsObj = tie %Args, 'XPDFJ::Args';
	{
		no strict 'refs';
		*{$safe->root.'::Args'} = \%Args;
	}
	@args{qw(safe Args ArgsObj VERSION)} = ($safe, \%Args, $ArgsObj, $VERSION);
	$args{dopath} ||= '';
	$args{verbose} ||= 0;
	$args{debuginfo} ||= 0;
	my $self = bless \%args, $class;
	$self;
}

sub verbose {
	my($self, $value) = @_;
	if( defined $value ) {
		$self->{verbose} = $value;
	}
	$self->{verbose};
}

sub debuginfo {
	my($self, $value) = @_;
	if( defined $value ) {
		$self->{debuginfo} = $value;
	}
	$self->{debuginfo};
}

sub vprint {
	my($self, $msg, $level, $addindent) = @_;
	$level ||= 0;
	$addindent ||= 0;
	return if $self->verbose < $level;
	$DebugIndent =~ s/.$// if $addindent < 0;
	print "$DebugIndent$msg\n";
	$DebugIndent .= " " if $addindent > 0;
}

sub parsefile { 
	my($self, $file, %args) = @_;
	$self->vprint("parse '$file'");
	my $parser = new XML::Parser(Style => 'Tree');
	$self->{tree} = $parser->parsefile($file);
	$self->root_parse(\%args);
}

sub parse { 
	my($self, $data, %args) = @_;
	$self->vprint("parse data in memory");
	my $parser = new XML::Parser(Style => 'Tree');
	$self->{tree} = $parser->parse($data);
	$self->root_parse(\%args);
}

sub root_parse {
	my($self, $args) = @_;
	my($element) = $self->elements($self->{tree});
	my($tag, $attributes, $children) = @$element;
	die "root must be 'XPDFJ'" if $tag ne 'XPDFJ';
	my %args = $self->args($attributes);
	my $version = delete $args{version};
	die "version '$version' required but my version is '$VERSION'"
		if $version && $version > $VERSION;
	%args = (%args, %$args) if ref($args) eq 'HASH';
	$self->method_parse($children, undef, \%args);
}

sub method_parse {
	my($self, $tree, $this, $args, $withtext, $locallevel) = @_;
	my @result;
	my $current_locallevel;
	if( defined $locallevel || $args ) {
		$self->enter_local($args, $locallevel);
	}
	for my $elem($self->elements($tree)) {
		my($tag, $attributes, $children) = @$elem;
		if( $tag eq '0' ) {
			next unless $withtext;
			$children = $self->var($children) if $children =~ /$VarnamePtn/;
			if( $withtext eq 'autonl' ) {
				push @result, autonl($children);
			} else {
				push @result, $children;
			}
		} else {
			push @result, $self->call_method($tag, $attributes, $children, $this);
		}
	}
	if( defined $locallevel || $args ) {
		$self->leave_local;
	}
	wantarray ? @result : @result <= 1 ? $result[0] : \@result;
}

sub call_method {
	my($self, $tag, $attributes, $children, $this) = @_;
	my @result;
	eval { # for error handling
	if( $self->{alias}{$tag} ) {
		my $aliasargs = $self->{aliasargs}{$tag};
		if( %$aliasargs ) {
			$attributes = {%$aliasargs, %$attributes};
		}
		$tag = $self->{alias}{$tag};
	}
	my $func = "do_$tag";
	if( $self->can($func) ) {
		$self->vprint("$func({@{[%$attributes]}}, ["._treeshow($children).
			"])", 1, 1);
		@result = $self->$func($attributes, $children, $this);
		$self->vprint("$func returns (@result)", 1, -1);
	} else {
		my $callchildren;
		($callchildren, $children) = $self->split_call($children);
		if( $self->{attributesname}{$tag} ) {
			$attributes = {$self->{attributesname}{$tag} =>
				{$self->args($attributes)}};
		}
		my %args;
		my $contentsmode = $self->{contentsmode}{$tag} || '';
		my $contentsname = $self->{contentsname}{$tag} || 'contents';
		if( $contentsmode eq '' ) {
			%args = $self->args($attributes, $children);
		} elsif( $contentsmode eq 'method' ) {
			%args = ($self->args($attributes), 
			$contentsname => [$self->method_parse($children, $this)]);
		} elsif( $contentsmode eq 'text' ) {
			%args = ($self->args($attributes), 
			$contentsname => [$self->method_parse($children, $this, undef, 1)]);
		} elsif( $contentsmode eq 'autonl' ) {
			%args = ($self->args($attributes), 
			$contentsname => 
			[$self->method_parse($children, $this, undef, 'autonl')]);
		} elsif( $contentsmode eq 'raw' ) {
			%args = ($self->args($attributes), 
			$contentsname => [$self->argslevel, $children]);
		} else {
			die "unknown contentsmode '$contentsmode'";
		}
		if( $self->{defargs}{$tag} ) {
			my %defargs = %{$self->{defargs}{$tag}};
			$self->subst_vars(\%defargs);
			for my $key(keys %defargs) {
				$args{$key} = $defargs{$key} unless defined $args{$key};
			}
		}
		my $call = delete $args{call};
		my %callargs = $self->args(undef, $callchildren);
		push @$call, @{$callargs{call}} if $callargs{call};
		my $varname = delete $args{setvar};
		$varname ||= '$Doc' if $tag eq 'Doc';
		if( $self->{def}{$tag} ) {
			$self->vprint("$tag(@{[%args]})", 1, 1);
			@result = $contentsmode eq 'raw' ?
				$self->method_parse($self->{def}{$tag}, $this, \%args, undef, 
					$self->argslevel) :
				$self->method_parse($self->{def}{$tag}, $this, \%args);
			$self->vprint("$tag returns (@result)", 1, -1);
		} elsif( $tag =~ /^[A-Z]/ ) {
			no strict 'refs';
			$self->vprint("$tag(@{[%args]})", 1, 1);
			@result = &$tag(\%args);
			$self->vprint("$tag returns (@result)", 1, -1);
			# $self->{docobj} = $result[0] if $tag eq 'Doc';
		} else {
			$this = delete $args{caller} if $args{caller};
			# $this ||= $self->{docobj};
			$this ||= $self->var('$Doc');
			die "missing 'caller' for $tag" unless $this;
			$self->vprint("$this->$tag(@{[%args]})", 1, 1);
			@result = $this->$tag(\%args);
			$self->vprint("$tag returns (".join(",", @result).")", 1, -1);
		}
		$self->var($varname, @result) if $varname;
		if( $call ) {
			for my $obj(@result) {
				for my $tree(@$call) {
					$self->method_parse($tree, $obj);
				}
			}
		}
	}
	}; # end of eval
	die "error in '$tag': $@" if $@;
	@result;
}

sub args {
	my($self, $attributes, $children, $nosubst) = @_;
	my %args;
	%args = %$attributes if ref($attributes) eq 'HASH';
	%args = $self->arg_parse($children, %args) if $children;
	$self->subst_vars(\%args, $nosubst);
	if( ref($args{attributes}) eq 'HASH' ) {
		my $tmp = delete $args{attributes};
		$self->subst_vars($tmp, $nosubst);
		%args = (%args, %$tmp);
	}
	%args;
}

sub arg_parse {
	my($self, $tree, %args) = @_;
	return %args unless ref($tree) eq 'ARRAY';
	for my $elem($self->elements($tree)) {
		my($tag, $attributes, $children) = @$elem;
		next if $tag eq '0';
		if( $tag eq 'call' ) {
			push @{$args{$tag}}, $children;
		} else {
			for my $elem($self->elements($children)) {
				my($ctag, $cattr, $cchildren) = @$elem;
				my @value;
				if( $ctag eq '0' ) {
					@value = ($cchildren);
				} else {
					@value = $self->call_method($ctag, $cattr, $cchildren);
				}
				next unless @value;
				if( !exists $args{$tag} ) {
					$args{$tag} = @value == 1 ? $value[0] : \@value;
				} elsif( ref($args{$tag}) eq 'ARRAY' ) {
					push @{$args{$tag}}, @value;
				} else {
					$args{$tag} = [$args{$tag}, @value];
				}
			}
		}
	}
	%args;
}

sub subst_var {
	my($self, $str) = @_;
	$str = $self->var($str) if $str =~ /$VarnamePtn/;
	$str;
}

sub subst_vars {
	my($self, $args, $nosubst) = @_;
	return if !ref($nosubst) && $nosubst;
	my @nosubst = ref($nosubst) eq 'ARRAY' ? @$nosubst : ();
	my $nonosubst = 0;
	if( @nosubst && $nosubst[0] eq '!' ) {
		shift @nosubst;
		$nonosubst = 1;
	}
	for my $key(keys %$args) {
		next if $key eq 'setvar' || 
			($nonosubst ? !grep {$_ eq $key} @nosubst : 
			grep {$_ eq $key} @nosubst);
		if( ref($args->{$key}) eq 'ARRAY' ) {
			grep {$_ = $self->var($_) if /$VarnamePtn/ } @{$args->{$key}};
		} elsif( $args->{$key} =~ /$VarnamePtn/ ) {
			$args->{$key} = $self->var($args->{$key});
		}
	}
}

sub package {
	my($self) = @_;
	$self->{safe}->root;
}

sub var {
	my($self, $name, @values) = @_;
	$self->_var(0, $name, @values);
}

sub var_local {
	my($self, $name, @values) = @_;
	$self->_var(1, $name, @values);
}

sub _var {
	my($self, $local, $name, @values) = @_;
	my $pkg = $self->package;
	my $key;
	($name, $key) = $name =~ /^\$?([A-Za-z_]\w*)(?:\{([A-Za-z_]\w*)\})?$/;
	$key ||= '';
	my $result;
	no strict 'refs';
	if( $key eq '' ) {
		if( $local ) {
			$self->vprint("local($self->argslevel) $name => ".
				(${$pkg.'::'.$name} || ''), 2);
			$self->{local}[$self->argslevel]{$name} = ${$pkg.'::'.$name};
		}
		if( @values ) {
			my $value = @values == 1 ? $values[0] : \@values;
			${$pkg.'::'.$name} = $value;
		}
		die "\$$name not defined" unless defined ${$pkg.'::'.$name};
		$result = ${$pkg.'::'.$name};
	} else {
		if( $local ) {
			$self->vprint("local(".$self->argslevel.") $name\{$key} => ".
				(${$pkg.'::'.$name} || ''), 2);
			$self->{local}[$self->argslevel]{"$name\{$key}"} = ${$pkg.'::'.$name}{$key};
		}
		if( @values ) {
			my $value = @values == 1 ? $values[0] : \@values;
			${$pkg.'::'.$name}{$key} = $value;
		}
		die "\$$name\{$key} not defined" unless defined ${$pkg.'::'.$name}{$key};
		$result = ${$pkg.'::'.$name}{$key};
	}
	$result;
}

sub set_args {
	my($self, $args) = @_;
	if( defined $args && ref($args) eq 'HASH' ) {
		$self->vprint("add args (".$self->argslevel.") {", 2);
		for my $attr(keys %$args) {
			$self->vprint("  $attr => $args->{$attr}", 2);
			$self->{Args}{$attr} = $args->{$attr};
		}
		$self->vprint("}", 2);
	}
}

sub argslevel {
	my($self) = @_;
	$self->{ArgsObj}->level;
}

sub argsnext {
	my($self, $level) = @_;
	$self->{ArgsObj}->next($level);
}

sub argsprev {
	my($self) = @_;
	$self->{ArgsObj}->prev;
}

sub Xargsaliaslevel {
	my($self) = @_;
	$self->{ArgsObj}->aliaslevel;
}

sub enter_local {
	my($self, $args, $argslevel) = @_;
	die "Args level $argslevel over run" 
		if defined $argslevel && $argslevel > $self->argslevel;
	$self->argsnext($argslevel);
	$self->vprint("enter -->(".$self->argslevel.")", 2, 1);
	my $level = $self->argslevel;
	$self->{local}[$level] = {};
#	if( defined $argslevel && ref($args) eq 'HASH' ) {
#		$self->vprint("save local variables {", 2);
#		for my $name(keys %$args) {
#			$self->vprint("  \$Args{$name} => $self->{Args}{$name}", 2);
#			$self->{local}[$level]{"\$Args{$name}"} = $self->{Args}{$name};
#		}
#		$self->vprint("}", 2);
#	}
	$self->set_args($args);
}

sub leave_local {
	my($self) = @_;
	my $pkg = $self->package;
	my $locals = $self->{local}[$self->argslevel];
	if( ref($locals) eq 'HASH' ) {
		no strict 'refs';
		$self->vprint("restore local variables {", 2);
		for my $name(keys %$locals) {
			$self->vprint("  $name => $locals->{$name}", 2);
			$self->var($name, $locals->{$name});
		}
		$self->vprint("}", 2);
	}
	$self->vprint("<-- leave(".$self->argslevel.")", 2, -1);
	$self->argsprev;
}

sub eval {
	my($self, $code) = @_;
	if( $] > 5.007 ) {
		$code = 'BEGIN{&$bytesimport();} local $^W = 0; ' . $code;
	} else {
		$code = 'local $^W = 0; ' . $code;
	}
	$self->{safe}->reval($code);
}

sub split_call {
	my($self, $tree) = @_;
	return unless ref($tree) eq 'ARRAY';
	my(@call, @tmptree);
	for( my $j = 0; $j < @$tree - 1; $j += 2 ) {
		my($tag, $children) = ($tree->[$j], $tree->[$j + 1]);
		next if $tag eq '0' && $children =~ /^\s+$/ && $children =~ /[\r\n]/;
		if( $tag eq 'call' ) {
			push @call, $tag, $children;
		} else {
			push @tmptree, $tag, $children;
		}
	}
	(\@call, \@tmptree);
}

sub elements {
	my($self, $tree) = @_;
	#_elements($tree, $self->{alias});
	_elements($tree);
}

sub _elements {
	my($tree, $alias) = @_;
	my @elements;
	for( my $j = 0; $j < @$tree - 1; $j += 2 ) {
		my($tag, $children) = ($tree->[$j], $tree->[$j + 1]);
		next if $tag eq '0' && $children =~ /^\s+$/ && $children =~ /[\r\n]/;
		$tag = $alias->{$tag} if $alias && $alias->{$tag};
		my $attributes;
		if( ref($children) eq 'ARRAY' ) {
			my @children = @$children;
			$attributes = shift @children;
			my %tmp = %$attributes;
			$attributes = \%tmp;
			$children = \@children;
		}
		push @elements, [$tag, $attributes, $children];
	}
	@elements;
}

sub _treeshow {
	my($tree, $deep) = @_;
	$deep ||= 0;
	my $result = '';
	for( my $j = 0; $j < @$tree - 1; $j += 2 ) {
		my($tag, $children) = ($tree->[$j], $tree->[$j + 1]);
		next if $tag eq '0' && $children =~ /^\s+$/ && $children =~ /[\r\n]/;
		if( $tag eq '0' ) {
			$result .= $children;
		} elsif( $deep && ref($children) eq 'ARRAY' ) {
			my $attr = shift @$children;
			$result .= "<$tag";
			if( keys %$attr ) {
				$result .= " ";
				$result .= join(" ", map {"$_=\"$attr->{$_}\""} keys %$attr);
			}
			$result .= ">";
			$result .= _treeshow($children, $deep);
			$result .= "</$tag>";
		} else {
			$result .= "<$tag...>";
		}
	}
	$result;
}

#---------------------
# internal method
#---------------------

sub do_require {
	my($self, $attributes, $children) = @_;
	my %args = $self->args($attributes, $children);
	die "version '$args{XPDFJ}' required but my version is '$VERSION'"
		if $args{XPDFJ} && $args{XPDFJ} > $VERSION;
	return;
}

sub do_eval {
	my($self, $attributes, $children) = @_;
	$self->_do_eval(0, $attributes, $children);
}

sub do_reval {
	my($self, $attributes, $children) = @_;
	$self->_do_eval(1, $attributes, $children);
}

sub _do_eval {
	my($self, $return, $attributes, $children) = @_;
	my $code = $self->method_parse($children, undef, undef, 1);
	my @result = $self->eval($code);
	die "eval error: $@: '$code'" if $@;
	return unless $return;
	@result;
}

sub do_for {
	my($self, $attributes, $children, $this) = @_;
	my %args = $self->args($attributes, undef, [qw(eval)]);
	my $varname = delete $args{setvar};
	my $eval = delete $args{eval};
	my @list = $self->eval($eval);
	@list = @{$list[0]} if @list == 1 && ref($list[0]) eq 'ARRAY';
	for my $value(@list) {
		$self->var($varname, $value);
		$self->method_parse($children, $this, \%args);
	}
	return;
}

sub do_def {
	my($self, $attributes, $children) = @_;
	my %args = $self->args($attributes, undef, 
		[qw(! tag attributesname contentsname)]);
	my $tag = delete $args{tag};
	my $attributesname = delete $args{attributesname};
	my $contentsname = delete $args{contentsname};
	my $contentsmode = delete $args{contentsmode};
	$self->{def}{$tag} = $children;
	$self->{attributesname}{$tag} = $attributesname if $attributesname;
	$self->{contentsname}{$tag} = $contentsname if $contentsname;
	$self->{contentsmode}{$tag} = $contentsmode if $contentsmode;
	$self->{defargs}{$tag} = \%args if %args;
	return;
}

sub do_alias {
	my($self, $attributes, $children) = @_;
	my %args = $self->args($attributes, $children, [qw(! tag aliasof)]);
	my $tag = delete $args{tag};
	my $aliasof = delete $args{aliasof};
	$self->{alias}{$tag} = $aliasof;
	$self->{aliasargs}{$tag} = \%args;
	return;
}

sub do_local {
	my($self, $attributes, $children) = @_;
	my %args = $self->args($attributes, undef, [qw(eval)]);
	my $varname = delete $args{setvar};
	my $eval = delete $args{eval};
	my @list = $eval ? $self->eval($eval) : ();
	$self->var_local($varname, @list);
	return;
}

sub do_do {
	my($self, $attributes, $children, $this) = @_;
	my %args = $self->args($attributes, undef, [qw(if unless result)]);
	my $if = delete $args{if};
	if( defined $if ) {
		return unless $self->eval($if);
	}
	my $unless = delete $args{unless};
	if( defined $unless ) {
		return if $self->eval($unless);
	}
	$this = delete $args{caller} if $args{caller};
	my $varname = delete $args{setvar};
	my $result = delete $args{result} || '';
	my $file = delete $args{file};
	my $contents = delete $args{contents};
	my $locallevel;
	my $withtext = delete $args{withtext};
	my $local = delete $args{local};
	my $verbose = delete $args{verbose};
	my $args = %args ? \%args : $local ? {} : undef;
	if( $file ) {
		my @path = split(/\s;\s/, $self->{dopath});
		unless( -e $file ) {
			my $found = 0;
			for my $path( @path ) {
				if( -e "$path/$file" ) {
					$file = "$path/$file";
					$found = 1;
				}
			}
			die "missing file '$file'" unless $found;
		}
		$self->vprint("do '$file'");
		my $parser = new XML::Parser(Style => 'Tree');
		$children = $parser->parsefile($file);
	} elsif( $contents ) {
		die "illegal 'contents' of do" unless ref($contents) eq 'ARRAY';
		($locallevel, $children) = @$contents;
	}
	my $oldverbose;
	if( defined $verbose ) {
		$oldverbose = $self->verbose + 0;
		$self->verbose($verbose);
	}
	my @result = $self->method_parse($children, $this, $args, $withtext, 
		$locallevel); 
	if( defined $verbose ) {
		$self->verbose($oldverbose);
	}
	$self->var($varname, @result) if $varname;
	if( $result eq 'first' ) {
		@result = shift @result;
	} elsif( $result eq 'last' ) {
		@result = pop @result;
	} elsif( $result eq 'null' ) {
		@result = ();
	} elsif( $result =~ /$VarnamePtn/ ) {
		@result = ($self->var($result));
	}
	@result;
}

sub do_sub {
	my($self, $attributes, $children, $this) = @_;
	return sub { $self->method_parse($children, $this); };
}

sub do_debuginfo {
	my($self, $attributes, $children, $this) = @_;
	return unless $self->{debuginfo};
	my %args = $self->args($attributes);
	my $pattern = delete $args{pattern};
	print "argslevel: ".$self->argslevel."\n";
	my $pkg = $self->package;
	no strict 'refs';
	my $tab = \%{$pkg.'::'};
	for my $name(keys %$tab) {
		next if $pattern && $name !~ /$pattern/;
		if( defined ${$tab->{$name}} ) { 
			if( ref(${$tab->{$name}}) eq 'ARRAY' ) {
				print "  $name => [", join(",", @{${$tab->{$name}}}), "]\n";
			} else {
				print "  $name => ${$tab->{$name}}\n";
			}
		}
		if( defined %{$tab->{$name}} && $name !~ /::$/ ) { 
			print "  $name => {\n";
			for my $key(keys %{$tab->{$name}}) {
				if( ref(${$tab->{$name}}{$key}) eq 'ARRAY' ) {
					print "    $key => [", join(",", @{${$tab->{$name}}{$key}})  ,"]\n";
				} else {
					print "    $key => ",${$tab->{$name}}{$key},"\n";
				}
			}
			print "  }\n";
		}
	}
	return;
}

# utility subroutines for eval package

sub istext {
	my($tree) = @_;
	return 1 unless ref($tree);
	return 0 unless ref($tree) eq 'ARRAY';
	$tree->[0] eq '0';
}

sub addcomma {
	my($num) = @_;
	$num += 0;
	while( $num =~ s/(\d)(\d\d\d)(?!\d)/$1,$2/g ) {}
	$num;
}

sub autonl {
	my($str) = @_;
	my @result;
	for my $part(split /[ \t]*\n[ \t]*/, $str) {
		next if $part eq '';
		push @result, $part, NewLine;
	}
	pop @result;
	@result;
}

#---------------------------------------
# for %Args
#---------------------------------------
package XPDFJ::Args;
use Carp;
use strict;

sub TIEHASH {
	my($class) = @_;
	bless {slot => [{}], parentlevel => [-1], level => 0}, $class;
}

sub DESTROY {
}

sub FETCH {
	my($self, $key) = @_;
	my $level = $self->level;
	while( $level >= 0 ) {
		if( exists $self->{slot}[$level]{$key} ) {
			return $self->{slot}[$level]{$key};
		}
		$level = $self->parentlevel($level);
	}
	return;
}

sub STORE {
	my($self, $key, $value) = @_;
	my $level = $self->level;
	return $self->{slot}[$level]{$key} = $value;
}

sub DELETE {
	my($self, $key) = @_;
	my $level = $self->level;
	my $result;
	while( $level >= 0 ) {
		if( exists $self->{slot}[$level]{$key} ) {
			my $tmp = delete $self->{slot}[$level]{$key};
			$result = $tmp unless defined $result;
		}
		$level = $self->parentlevel($level);
	}
	return $result;
}

sub EXISTS {
	my($self, $key) = @_;
	my $level = $self->level;
	while( $level >= 0 ) {
		if( exists $self->{slot}[$level]{$key} ) {
			return 1;
		}
		$level = $self->parentlevel($level - 1);
	}
	return;
}

sub FIRSTKEY {
	my($self) = @_;
	my %keys;
	my $level = $self->level;
	while( $level >= 0 ) {
		%keys = (%keys, map {$_ => 1} keys %{$self->{slot}[$level]});
		$level = $self->parentlevel($level);
	}
	$self->{keys} = [keys %keys];
	$self->{keys}[0];
}

sub NEXTKEY {
	my($self, $key) = @_;
	my $j = -1;
	for( $j = 0; $j < @{$self->{keys}}; $j++ ) {
		last if $self->{keys}[$j] eq $key;
	}
	if( $j >= 0 && $j < @{$self->{keys}} - 1 ) {
		return $self->{keys}[$j + 1];
	} else {
		return;
	}
}

sub level {
	my($self) = @_;
	$self->{level};
}

sub Xaliaslevel {
	my($self, $level) = @_;
	$level = $self->{level} unless defined $level;
	return $level if $level < 0;
	while( $self->{aliaslevel}[$level] >= 0 ) {
		$level = $self->{aliaslevel}[$level];
	}
	$level;
}

sub parentlevel {
	my($self, $level) = @_;
	$level = $self->{level} unless defined $level;
	return $level if $level < 0;
	$self->{parentlevel}[$level];
}

sub next {
	my($self, $parentlevel) = @_;
	croak "parentlevel $parentlevel over run" 
		if defined $parentlevel && $parentlevel > $self->level;
	$parentlevel ||= $self->{level};
	$self->{level}++;
	$self->{parentlevel}[$self->{level}] = $parentlevel;
	$self->{slot}[$self->{level}] = {};
	$self->{level};
}

sub prev {
	my($self) = @_;
	--$self->{level};
}

1;

