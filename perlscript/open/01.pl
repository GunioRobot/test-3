#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

my $filename = 'test.txt';
open my $fh, "<", $filename;

my $filebody = $fh;

print "------------\n";
print "$fh\n";
print "------------\n";
print "$filebody\n";
print "------------\n";
print Dumper $fh;
print "------------\n";

close $fh;

exit(1);
