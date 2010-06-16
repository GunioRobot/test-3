#!/usr/bin/perl

use strict;
use warnings;

my $ref_func;

{
  my $number = 0;
  $ref_func = sub {
    my $str = shift;

    $number++;
    print "$number: $str\n";
  };
}

$ref_func->('abcdef');
$ref_func->('AAA');
$ref_func->('xyz');
$ref_func->('AzureStone');
$ref_func->('hogehoge');



