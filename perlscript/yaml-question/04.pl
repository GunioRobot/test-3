#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

use YAML;

my $yaml = YAML::LoadFile('./conf.d/01.yml');

print Dumper $yaml;

print "$yaml->{fruit}->[0]\n";

foreach (@{$yaml->{fruit}}) {
  print "$_\n";
}



sub DESTROY {
  print "destory\n";
}


