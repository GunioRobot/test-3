#!/usr/bin/perl

use strict;
use warnings;

use CGI::Simple;
use Template;

use Data::Dumper;

my $tt  = new Template();
$tt->process('surl.tt');



1;
