#!/usr/bin/perl -l

@month = ('January','February','March','April','May','June','July','August','September','October','November','December');

$refMonth = \@month;

# 
print "refMonth: $refMonth -> @$refMonth \n";

1;
