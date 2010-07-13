#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;
use List::Util qw(min);


my %hash = (
  12 => '1354',
  193 => '6543',
);

my @vector = %hash;

print Dumper @vector;


my $test = min @vector;

print "$test\n";



exit(1);



