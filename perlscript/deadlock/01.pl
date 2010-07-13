#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

print "hoge\n";

open my $fh, '>>', hoge.txt or die $!;
  my $hogehoge = 'hoge';
  print $fh $hogehoge, "\n";
close $fh;

#sleep 60;
print "hoge end\n";
