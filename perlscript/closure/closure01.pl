#!/usr/bin/perl -l 

use strict;
use warnings;

sub make_counter {
  my ($start, $interval) = @_;
  $start-=$interval;
  return sub { $start+=$interval; }
}

my $from_ten = make_counter(10,3);
my $from_four = make_counter(4,5);

print $from_ten->();
print $from_ten->();
print $from_four->();
print $from_ten->();
print $from_four->();

1;
