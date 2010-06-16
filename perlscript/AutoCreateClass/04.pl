#!/usr/bin/perl

# Normal 
use strict;
use warnings;
use Data::Dumper;

package main;
Test::A->view; Test::B->view;
Test::C->view; Test::D->view;
Test::E->view;

print "--------------------------------------\n";

my @class_name = qw{Test::A Test::B Test::C Test::D Test::E};

foreach (@class_name) {
  print $_->view;
}

exit(1);

package Test::A;
sub view { print "Class is a Test::A \n"; }

package Test::B;
sub view { print "Class is a Test::B \n"; }

package Test::C;
sub view { print "Class  is a Test::C \n"; } 

package Test::D;
sub view { print "Class is a Test::D \n"; }

package Test::E;
sub view { print "Class is a Test::E \n"; }

