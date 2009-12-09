#!/usr/bin/perl

use strict;
use warnings;

use WWW::Mechanize;
use YAML::Tiny;

my %input_num;
my $result_numbers = "";

$input_num{'start'}  = $ARGV[0]; 
$input_num{'end'}    = $ARGV[1];

foreach ( $input_num{'start'}..$input_num{'end'} ) { 
  if (sqrt($_) =~ /^\d+$/) {
    $result_numbers = $result_numbers . $_ . ',';
  }
}

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

#print $mech->{last_uri} . "\n";
`firefox -url $mech->{last_uri}`;

1;
