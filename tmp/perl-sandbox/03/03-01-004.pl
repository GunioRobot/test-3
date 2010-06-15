#!/usr/bin/perl -l

use strict;
use warnings;

use Data::Dumper;
sub ddp ($) { print Data::Dumper::Dumper(shift);  }

my $rm1    = 'January';
my $rm2    = 'February';
my $rm3    = 'March';
my $rm4    = 'April';
my $rm5    = 'May';
my $rm6    = 'June';
my $rm7    = 'July';
my $rm8    = 'August';
my $rm9    = 'September';
my $rm10   = 'October';
my $rm11   = 'November';
my $rm12   = 'December';

my @refMonth = (\$rm1, \$rm2, \$rm3, \$rm4, \$rm5, \$rm6, \$rm7, \$rm8, \$rm9, \$rm10, \$rm11, \$rm12);

print "${$refMonth[4]}";

ddp @refMonth;

foreach (@refMonth) {
  ddp $_;
}



1;
