#!/usr/bin/perl -l 

use strict;
use warnings;

my $ref_func = sub {
  print "OK";
};

$ref_func->();

1;
