#!/usr/bin/perl

use strict;
use warnings;

use Date::Simple;

my $date  = Date::Simple->new();

print $date->format('%Y/%m/%d') . "\n";

1;
