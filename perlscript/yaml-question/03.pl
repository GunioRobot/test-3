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

my $test02 = $test->{'01.yml'};
my $test03 = %{$test02};
print $test03;

exit(1);
