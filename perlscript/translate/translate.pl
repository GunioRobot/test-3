#!/usr/bin/perl

use strict;
use warnings;

use YAML::Tiny;
#use WWW::Mechanize;
use Data::Dumper;

our $VERSION  = '0.1';

my $yaml  = YAML::Tiny->new;
$yaml     = YAML::Tiny->read('config.yaml');

#package Acme::Translate::google;
#package Acme::Translate::excite;
#package Acme::Translate::infoseek;
#package Acme::Translate::yahoo;

&google;

sub google{;
#  my ( $body, $method )  = @_;

  use WWW::Mechanize;
  my $mech  =   new WWW::Mechanize( autocheck=>1 );
  $mech->get($yaml->[0]->{google}->{url});   

  print Dumper $mech->content;

}

sub excite {
#  my ( $body, $method )  = @_;

  use WWW::Mechanize;
  my $mech  = new WWW::Mechanize( autocheck=>1 );
  $mech->get($yaml->[0]->{excite}->{url});

  print Dumper $mech->content;
}

sub infoseek {
#  my ( $body, $method )  = @_;

  use WWW::Mechanize( autocheck=>1 );
  my $mech  = new WWW::Mechanize( autocheck=>1);
  $mech->get($yaml->[0]->{infoseek}->{url});

  print Dumper $mech->content;
}

sub yahoo {
#  my ( $body, $method )  = @_;

  use WWW::Mechanize;
  my $mech  = new WWW::Mechanize( autocheck=>1 );
  $mech->get($yaml->[0]->{yahoo}->{url});

  print Dumper $mech->content;

}
1;
