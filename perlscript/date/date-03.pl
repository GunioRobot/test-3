#!/usr/bin/perl -l

use strict;
use warnings;

use Date::Simple;
use Data::Dumper;

my $date  = Date::Simple->new();

print $date->format('%Y/%m/%d');
print $date->format('%H時%M分');
print $date->format('%H:%M:%S');

print "------------------------------";
print Dumper $date->format;
print "------------------------------";
print Dumper $date;

1;
