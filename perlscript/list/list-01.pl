#!/usr/bin/perl -l

use strict;
use warnings;

use Data::Dumper;

use List::MoreUtils qw(:all);

my $v;
my @lists = (1, 2, 4, 8, 16);

$v = any {$_ < 10 }@lists;
print Dumper $v;

my $v = all {$_ < 10} @lists;
print Dumper $v;

my $test;
undef $test;
print Dumper $test;


