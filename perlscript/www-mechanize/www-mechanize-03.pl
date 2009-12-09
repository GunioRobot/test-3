#!/usr/bin/perl

use strict;
use warnings;

use WWW::Mechanize;
use YAML::Tiny;

my $result_numbers  = '1,4,9,16,25,36,49,64,81,100,';

my $yaml  = YAML::Tiny->new;
$yaml     = YAML::Tiny->read('config.yaml');

my $mech  = new WWW::Mechanize( autocheck=>1 );

$mech->get( $yaml->[0]->{sloan}->{url} );

$mech->submit_form(
  fields => {
    q         =>  $result_numbers,
    language  =>  'japanese',
    go        =>  '検索',
  },
);

print $mech->{last_uri} . "\n";

1;
