# pod2pdf.pl - PDFJ sample script
# 2002 <nakajima@netstock.co.jp>

# !!! CAUTION !!!
# This script contains Japanese characters. Please save this file 
# with the Japanese character code you use for the target text, and
# choice same code at following 'use PDFJ ...'.

#--------------------------------------------------------------------
package PodPdf;

# !!! Choice 'SJIS or 'EUC' !!!
use PDFJ 'SJIS';
#use PDFJ 'EUC';

use Pod::Parser;
#use Data::Dumper;
use strict;
use vars qw(@ISA);

@ISA = qw(Pod::Parser);

sub initialize {
	my($self) = @_;
	$self->SUPER::initialize();
	my $doc = PDFJ::Doc->new(1.2, 595, 842); # A4
	my $width = 595 - 72 - 72;
	my $height = 842 - 72 - 72;
	$self->{bodywidth} = $width;
	$self->{bodyheight} = $height;
	my $f_normal = $doc->new_font('Ryumin-Light', '90ms-RKSJ-H', 'Times-Roman');
	my $f_italic = $doc->new_font('Ryumin-Light', '90ms-RKSJ-H', 'Times-Italic');
	my $f_bold = $doc->new_font('GothicBBB-Medium', '90ms-RKSJ-H', 'Times-Bold');
	my $f_bolditalic = 
		$doc->new_font('GothicBBB-Medium', '90ms-RKSJ-H', 'Times-BoldItalic');
	my $f_fix = $doc->new_font('GothicBBB-Medium', '90ms-RKSJ-H');
	my $f_gothic = 
		$doc->new_font('GothicBBB-Medium', '90ms-RKSJ-H', 'Helvetica');
	$doc->italic($f_normal, $f_italic, $f_bold, $f_bolditalic);
	$doc->bold($f_normal, $f_bold, $f_italic, $f_bolditalic);
	$self->{pdfdoc} = $doc;
	$self->{tstyle} = {
		head1 => TStyle(font => $f_gothic, fontsize => 15, objalign => 'm'),
		head2 => TStyle(font => $f_gothic, fontsize => 13),
		defitem => TStyle(font => $f_gothic, fontsize => 10),
		normal => TStyle(font => $f_normal, fontsize => 10),
		fix => TStyle(font => $f_fix, fontsize => 10),
		footer => TStyle(font => $f_gothic, fontsize => 9),
	};
	$self->{pstyle} = {
		head1 => PStyle(size => $width, linefeed => '100%', align => 'b', preskip => 30, postskip => 15, nobreak => 1, postnobreak => 1),
		head2 => PStyle(size => $width, linefeed => '100%', align => 'b', preskip => 20, postskip => 10, nobreak => 1, postnobreak => 1),
		defitem => PStyle(size => $width, linefeed => '100%', align => 'b', preskip => 10, postskip => 2.5, nobreak => 1, postnobreak => 1),
		normal => PStyle(size => $width, linefeed => '150%', align => 'w', preskip => 2.5, postskip => 2.5),
		verbatim => PStyle(size => $width, linefeed => '150%', align => 'w', preskip => 7.5, postskip => 7.5),
		footer => PStyle(size => $width, linefeed => '100%', align => 'm'),
	};
	$self->{listskip} = 5;
	$self->{head2mark} = '¡';
	$self->{bullmark} = 'E';
	$self->{indentunit} = 4;
}

sub pdfpara {
	my($self, $text, $stylename, $outlinelevel, $outlinetitle, $line) = @_;
	my $tstyle = $self->{tstyle}{$stylename} or 
		die "unknown style name $stylename\n";
	my $pstyle = $self->{pstyle}{$stylename} or 
		die "unknown style name $stylename\n";
	my @texts;
	push @texts, Shape->line(0, 0, $self->{bodywidth}, 0) if $line;
	if( defined $outlinelevel ) {
		$outlinetitle ||= $text;
		push @texts, Outline($outlinetitle, $outlinelevel), Dest($outlinetitle), 
			$text;
	} else {
		push @texts, $text;
	}
	Paragraph(Text([@texts], $tstyle), $pstyle);
}

sub add_pdfpara {
	my($self, $pdfpara) = @_;
	push @{$self->{pdfparas}}, $pdfpara;
}

sub status {
	my($self, $status) = @_;
	$self->{status} = $status if defined $status;
	$self->{status};
}

sub indent {
	my($self, $indent) = @_;
	$self->{indent} = $indent if defined $indent;
	$self->{indent} || 0;
}

sub itemnum {
	my($self, $itemnum) = @_;
	$self->{itemnum} = $itemnum if defined $itemnum;
	$self->{itemnum};
}

sub print {
	my($self) = @_;
	$self->{pdfdoc}->print($self->output_file);
}

sub end_pod {
	my($self) = @_;
	my $block = Block('V', $self->{pdfparas}, BStyle());
	for my $part( $block->break($self->{bodyheight}) ) {
		my $page = $self->{pdfdoc}->new_page;
		$part->show($page, 72, 72 + $self->{bodyheight});
		my $footer = $self->pdfpara($page->pagenum, 'footer');
		$footer->show($page, 72, 36);
	}
}

sub command {
	my($self, $command, $text, $linenum, $para) = @_;
	my $ptext = $text;
	$ptext =~ s/\n+$//;
	if( $command eq 'head1' ) {
		$self->status('normal');
		$self->add_pdfpara($self->pdfpara($ptext, 'head1', 0, $ptext, 1));
	} elsif( $command eq 'head2' ) {
		$self->status('normal');
		$self->add_pdfpara($self->pdfpara($self->{head2mark}.$ptext, 'head2', 
			1, $ptext));
	} elsif( $command eq 'over' ) {
		my($indent) = $ptext =~ /(\d+)/;
		$self->status('list');
		$self->indent($indent);
		$self->add_pdfpara($self->{listskip});
	} elsif( $command eq 'back' ) {
		$self->status('normal');
		$self->indent(0);
		$self->add_pdfpara($self->{listskip});
	} elsif( $command eq 'item' ) {
		if( $ptext eq '*' ) {
			$self->status('bullitem');
		} elsif( $ptext =~ /^(\d+)$/ ) {
			$self->status('numitem');
			$self->itemnum($1);
		} else {
			$self->add_pdfpara($self->pdfpara($ptext, 'defitem'));
			$self->status('normal');
		}
	}
}

sub verbatim {
	my($self, $text, $linenum, $para) = @_;
	$text =~ s/\n+$//s;
	my @texts;
	for my $line(split(/\n/, $text)) {
		push @texts, Text($line, $self->{tstyle}{fix}), NewLine;
	}
	my $indent = $self->indent * $self->{indentunit};
	my $pstyle = $self->{pstyle}{verbatim}->
		clone(beginindent => $indent, align => 'b');
	$self->add_pdfpara(Paragraph(Text([@texts], $self->{tstyle}{normal}), $pstyle));
}

sub toText {
	my($self, $root) = @_;
	my @texts;
	for my $part(@{$root->{text}}) {
		if( ref($part) ) {
			push @texts, $self->toText($part);
		} else {
			push @texts, $part;
		}
	}
	if( $root->{cmd} ) {
		my $cmd = $root->{cmd};
		my $style = TStyle();
		if( $cmd eq 'I' || $cmd eq 'F' ) {
			$style->{italic} = 1;
		} elsif( $cmd eq 'B' ) {
			$style->{bold} = 1;
		} elsif( $cmd eq 'C' ) {
			$style->{font} = $self->{tstyle}{fix}{font};
		} elsif( $cmd eq 'L' ) {
			my $dest = $texts[0];
			my $ptext;
			($ptext, $dest) = split /\|/, $dest if $dest =~ /\|/;
			if( $dest =~ /^\/?\"(.+)\"$/ ) {
				$dest = $1;
				$dest = "URI:$dest" if $dest =~ /^(https?|ftp|mailto):/i;
				$style->{withbox} = 'b';
				$style->{withboxstyle} = SStyle(link => $dest);
				$ptext ||= $dest;
			} else {
				$ptext ||= $dest;
			}
			$texts[0] = $ptext;
		} elsif( $cmd eq 'X' ) {
			my $dest = $texts[0];
			$texts[0] = Dest($dest);
		}
		Text(@texts, $style);
	} else {
		@texts;
	}
}

sub myinterpolate {
	my($self, $text) = @_;
	my $root = {text => []};
	my $cur = $root;
	while( $text =~ /\x01.|\x02/ ) {
		my $left = $`;
		my $sep = $&;
		$text = $';
		push @{$cur->{text}}, $left if $left ne '';
		if( $sep eq "\x02" ) {
			$cur = $cur->{parent};
		} else {
			my $cmd = substr($sep, 1, 1);
			my $newcur = {parent => $cur, cmd => $cmd, text => []};
			push @{$cur->{text}}, $newcur;
			$cur = $newcur;
		}
	}
	push @{$cur->{text}}, $text if $text ne '';
	$self->toText($root);
}

sub textblock {
	my($self, $text, $linenum, $para) = @_;
	$text = $self->interpolate($text, $linenum);
	$text =~ s/\n+$//;
	$text =~ s/\n/ /g;
	my @texts = $self->myinterpolate($text);
	my $indent = $self->indent;
	my $pstyle;
	if( $self->status eq 'bullitem' ) {
		$pstyle = $self->{pstyle}{normal}->clone(
			labeltext => Text($self->{bullmark}, $self->{tstyle}{normal}), 
			labelsize => $indent * $self->{indentunit});
		$self->status('normal');
	} elsif( $self->status eq 'numitem' ) {
		$pstyle = $self->{pstyle}{normal}->clone(
			labeltext => Text($self->{itemnum}, $self->{tstyle}{normal}), 
			labelsize => $indent * $self->{indentunit});
		$self->status('normal');
	} else {
		$pstyle = $self->{pstyle}{normal}->
			clone(beginindent => $indent * $self->{indentunit});
	}
	$self->add_pdfpara(Paragraph(Text(@texts, $self->{tstyle}{normal}), $pstyle));
}

my %Esc = qw(lt < gt > sol / verbar |);
sub interior_sequence {
	my($self, $command, $text, $seq) = @_;
	if( $command =~ /^[IBCLFX]$/ ) {
		"\x01$command$text\x02";
	} elsif( $command eq 'E' ) {
		$Esc{$text} || $text;
	} else {
		$text;
	}
}

#--------------------------------------------------------------------
package main;

my $podpdf = new PodPdf;
$podpdf->parse_from_file(@ARGV);
$podpdf->print;
