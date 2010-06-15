#!/usr/bin/perl -l

use strict;
use warnings;

my @tanka   = (200, 100, 300, 50, 2000);
my @kosuu   = (10, 20, 10, 50, 5);

print "kyou no uriage ==> " , &uriage(\@kosuu, \@tanka), "\n";

sub uriage {
  my ($ref_tanka, $ref_kosuu) = @_;
  my $uriage  = 0;
  for my $tanka (@$ref_tanka) {
    my $kosuu = shift @$ref_kosuu;
    $uriage += $tanka * $kosuu;
  } 
  return $uriage;
}

1;
