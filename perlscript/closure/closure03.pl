#!/usr/bin/perl 

use strict;
use warnings;

my $ref_func = sub {
  my $str = shift;
  print "$str\n";
};

$ref_func->('test');

1;
