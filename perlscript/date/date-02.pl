#!/usr/bin/perl

use strict;
use warnings;

use Date::Simple;

my $date  = Date::Simple->new();

print $date->format('%Y/%m/%d') . "\n";
print $date->format('%H時%M分') . "\n";
print $date->format('%H:%M:%S') . "\n";

1;
