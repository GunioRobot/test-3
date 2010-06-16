#!/usr/bin/perl 

use strict;
use warnings;

package test;

sub new {
  my ($class, $args)


}

sub disp {
  my ($class) = @_;
  print $class->{}
}

package main;

use test;

my $test = test->new(
  

);

$test->disp;



1;

