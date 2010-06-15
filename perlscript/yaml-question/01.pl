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
  #if ($@) {# later on}

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

YAML::DumpFile('test.yml', $data_struct);

print $data_struct->{'01.yml'};
#print $data_struct->{'01.yml'};

my $confirm_yaml = YAML::LoadFile('test.yml');

print $confirm_yaml->{'01.yml'}. "\n";


exit(1);

