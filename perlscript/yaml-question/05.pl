#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

use YAML;

my ($yaml,$data_struct);
my $ls = './conf.d/';

opendir INC, $ls or die "$ls:$!";

while (my $file = readdir INC) {
  next if $file =~ /^\.{1,2}$/;
  $yaml = eval { YAML::LoadFile("$ls/$file"); };
  if ($@) { print "$ls/$file is YAML Format Ero\n"; }
  else { print "$ls/$file is YAML Loading .....\n"; }

  if(ref($yaml) eq 'HASH') {
#    my %tmp_ref;
#    $data_struct = \%tmp_ref;
    
    foreach my $key (keys(%{$yaml})) {
      $data_struct->{$file}->{$key} = $yaml->{$key};
    }
  }

}
  print Dumper $data_struct;


closedir INC;

print "--------------------------------\n";
foreach my $key ($data_struct) {
  print Dumper $key;
}


exit(1);

