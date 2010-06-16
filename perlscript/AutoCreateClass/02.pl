#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

my @class = qw{Test::A Test::B Test::C Test::D Test::E};

foreach my $value (@class) {
  print "$value \n";
  {
    package "$value";
    sub view { print "Class is a $value \n"; }
  }
}

# ummmmmmm......
=pod
syntax error at ./02.pl line 12, near "package "$value""
syntax error at ./02.pl line 15, near "}"
Execution of ./02.pl aborted due to compilation errors.
=cut

 
exit(1);

