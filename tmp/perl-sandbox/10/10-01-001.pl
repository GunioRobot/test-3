#!/usr/bin/perl -l

use strict;
use warnings;

use Data::Dumper;
sub ddp ($) { print Data::Dumper::Dumper(shift); }

package Triangle;

sub space {
    ddp @_;
    my ($class, $a, $b, $c) = @_;
    warn "You are about to calculate the space of $class !!! \n";
    my $s = ($a + $b + $c) / 2;
    my $space = sqrt($s * ($s - $a) * ($s - $b) * ($s - $c));
    return $space;
}

package main;

my $a = 3;
my $b = 4;
my $c = 5;

my $space = Triangle->space($a,$b,$c);

print $space;


1;





