#!/usr/bin/perl

use strict;
use warnings;

use WWW::Mechanize;

my $result_numbers  = '1,4,9,16,25,36,49,64,81,100,';
my $jump_uri  = 'http://www.research.att.com/~njas/sequences/index.html?language=japanese';

my $mech  = new WWW::Mechanize( autocheck=>1 );

$mech->get($jump_uri);

$mech->submit_form(
  fields => {
    q         =>  $result_numbers,
    language  =>  'japanese',
    go        =>  '検索',
  },
);

print $mech->{last_uri} . "\n";

1;
