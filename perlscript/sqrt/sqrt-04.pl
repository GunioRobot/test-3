#!/usr/bin/perl

use strict;
use warnings;

my %input_num;

$input_num{'start'}  = $ARGV[0];
$input_num{'end'}    = $ARGV[1];
my $count;

foreach ( $input_num{'start'}..$input_num{'end'} ) {
  if (sqrt($_) =~ /^\d+$/) {
    print $_.',';
    ++$count;
  }
}

print "\n";

foreach ( $input_num{'start'}..$input_num{'end'} ) {
  if (sqrt($_) =~ /^\d+$/) {
    print sqrt($_).',';
    ++$count;
  }
}

print "\n---------------------\n";
print "$input_num{'start'} ～ $input_num{'end'}\n";
print "整数は、$count個です。\n";
print "---------------------\n";
print 'http://www.research.att.com/~njas/sequences/index.html?language=japanese'."\n";

1;
