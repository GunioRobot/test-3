#!/usr/bin/perl -l

use strict;
use warnings;

#for (my $i=1; $i<=100; $i++) {
#	print "$i FizzBuzz"; if     ($i%3 == 0 && $i%5 == 0 )
#  print "$i Fizz";     elsif  ($i%3 == 0)
#	print "$i Buzz";     elsif  ($i%5 == 0)
#	print "$i";          else
#}

foreach (1..100) {
  if ($_%3 == 0 && $_%5 == 0) { print "$_ FizzBuzz"; }
  elsif ($_%3 == 0)           { print "$_ Fizz"; }
  elsif ($_%5 == 0)           { print "$_ Buzz"; }
  else                        { print "$_"; }
}

1;
