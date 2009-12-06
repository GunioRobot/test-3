#!/usr/bin/perl

use strict;
use warnings;

use WWW::Mechanize;
use Data::Dumper;

my $mech  = new WWW::Mechanize( autocheck=>1 );

$mech->get('http://www.research.att.com/~njas/sequences/index.html?language=japanese');

1;
