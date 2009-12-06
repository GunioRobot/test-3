#!/usr/bin/perl -l

use strict;
use warnings;

my %input_num;

$input_num{'start'}  = $ARGV[0];
$input_num{'end'}    = $ARGV[1];
my $count;

foreach ( $input_num{'start'}..$input_num{'end'} ) {
  if (sqrt($_) =~ /^\d+$/) {
    print "$_ ->\t" . sqrt($_);
    ++$count;
  }
}
print "---------------------";
print "$input_num{'start'} ～ $input_num{'end'}";
print "整数は、$count個です。";

1;
