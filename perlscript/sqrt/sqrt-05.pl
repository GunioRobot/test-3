#!/usr/bin/perl

use strict;
use warnings;

my %input_num;

$input_num{'start'}  = $ARGV[0];
$input_num{'end'}    = $ARGV[1];

foreach ( $input_num{'start'}..$input_num{'end'} ) {
  if (sqrt($_) =~ /^\d+$/) {
    print $_.',';
  }
}

print "\n";

1;
