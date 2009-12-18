#!/usr/bin/perl

use strict;
use warnings;

use YAML::Tiny;

our $VERSION  = '0.1';

my $yaml  = YAML::Tiny->new;
$yaml     = YAML::Tiny->read('config.yaml');


#package google;

sub google{;
  my ( $body, $method )  = @_;
  print  $yaml->[0]->{google}->{url};
}

sub excite {
  my ( $body, $method )  = @_;
  print $yaml->[0]->{excite}->{url};
}

sub infoseek {
  my ( $body, $method )  = @_;
  print $yaml->[0]->{infoseek}->{url};
}

sub yahoo {
  my ( $body, $method )  = @_;
  print $yaml->[0]->{yahoo}->{url};
}
1;
