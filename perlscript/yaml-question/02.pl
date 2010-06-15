#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

my $test = {
  '01.yml' => {
    fruit => ['apple', 'strawberry','pear'],
  }, 
  '02.yml' => {
    fruit => ['apple','straverry','pear','plum'],
  },
};

print Dumper $test;

print $test->{'01.yml'};

exit(1);
