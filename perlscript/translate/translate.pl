#!/usr/bin/perl

use strict;
use warnings;

use YAML::Tiny;
use WWW::Mechanize;
use Data::Dumper;
#use Get::opt;
#use lib 'cpanlib';
#use lib 'lib';

our $VERSION  = '0.1';

my $yaml  = YAML::Tiny->new;
$yaml     = YAML::Tiny->read('config.yaml');

#package Acme::Translate::google;
#package Acme::Translate::excite;
#package Acme::Translate::infoseek;
#package Acme::Translate::yahoo;

&google;

sub google{;
  my ($body, $method)  = @_;
  
  my $mech  =   new WWW::Mechanize( autocheck=>1 );
  $mech->get($yaml->[0]->{google}->{url});   

  if ($method eq 'enja') {
  }
  elsif ($method eq 'jaen') {
  }
  else {
    print "例外が発生しました。\n";
  }

  print $mech->content;

}

sub excite {
  my ($body, $method)  = @_;

  my $mech  = new WWW::Mechanize( autocheck=>1 );
  $mech->get($yaml->[0]->{excite}->{url});

  if ($method eq 'enja') {
  }
  elsif ($method eq 'jaen') {
  }
  else {
    print "例外が発生しました。\n";
  }
  print $mech->content;
}

sub infoseek {
  my ($body, $method)  = @_;

  my $mech  = new WWW::Mechanize( autocheck=>1);
  $mech->get($yaml->[0]->{infoseek}->{url});

  if ($method eq 'enja') {
  }
  elsif ($method eq 'jaen') {
  }
  else {
    print "例外が発生しました。\n";
  }
  print $mech->content;
}

sub yahoo {
  my ($body, $method)  = @_;

  my $mech  = new WWW::Mechanize( autocheck=>1 );
  $mech->get($yaml->[0]->{yahoo}->{url});

  if ($method eq 'enja') {
  }
  elsif ($method eq 'jaen') {
  }
  else {
    print "例外が発生しました。\n";
  }
  print $mech->content;

}
1;
