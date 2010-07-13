#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

use List::Util qw(sum);
#my @hoges = (1,2,3,4,5,6);
my @hoges = ();

my %hoge = (
  Name => 'AzureStone',
  Age   => '18',
  Sex   => 'otoko'
);

push @hoges , \%hoge;

print Dumper @hoges;


#foreach my $key (@hoges) {
#  print "$key\n";
#}
map {print "$_->{'Age'}\n"} @hoges;


exit(1);
