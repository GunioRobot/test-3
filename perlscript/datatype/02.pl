#!/usr/bin/perl

use strict;
use warnings;
use Data::Dumper;

my @int_var   = (0,1,2,3,4,5);
my @char_var  = ("0","1","2","3","4","5");


printf("---------------------------------\n");

  if ($int_var[0] == 0) {
    print "this is a 0\n";
  }

  if ($int_var[0] == 1) {
    print "this is a 1\n";
  }

printf("---------------------------------\n");

  if ($int_var[0] == "0") {
    print "this is a 0\n";
  }

  if ($int_var[0] == "1") {
    print "this is a 1\n";
  }

printf("---------------------------------\n");

  if ($char_var[0] == 0) {
    print "this is a 0\n";
  }

  if ($char_var[0] == 1) {
    print "this is a 1\n";
  }

printf("---------------------------------\n");

  if ($char_var[0] == "0") {
    print "this is a 0\n";
  }

  if ($char_var[0] == "1") {
    print "this is a 1\n";
  }

printf("---------------------------------\n");

exit(1);

