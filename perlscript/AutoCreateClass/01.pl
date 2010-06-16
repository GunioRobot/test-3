#!/usr/bin/perl

# Normal 
use strict;
use warnings;
use Data::Dumper;

package main;
Test::A->view;


exit(1);

package Test::A;
sub view { print "Class is a Test::A \n"; }
1;

package Test::B;
sub view { print "Class is a Test::B \n"; }
1;

package Test::C;
sub view { print "Class  is a Test::C \n"; } 
1;

package Test::D;
sub view { print "Class is a Test::D \n"; }
1;

package Test::E;
sub view { print "Class is a Test::E \n"; }
1;

