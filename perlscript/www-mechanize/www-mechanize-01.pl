#!/usr/bin/perl

use strict;
use warnings;

use WWW::Mechanize;
use Data::Dumper;

my $mech  = new WWW::Mechanize( autocheck=>1 );

$mech->get('http://www.research.att.com/~njas/sequences/index.html?language=japanese');

$mech->submit_form(
  fields => {
    q => '1,4,9,16,25,36,49,64,81,100,',
    language=>'japanese',
    go=> '検索',
    },
);

print Dumper $mech;
1;
