#!/usr/bin/perl
# xpdfj.pl - XPDFJ sample script
# 2003 <nakajima@netstock.co.jp>
use XPDFJ;
use Getopt::Std;

getopt 'dv';
my $file = shift;
my $outfile = shift || "$file.pdf";
$opt_d ||= 0;
$opt_v ||= 0;
my $xpdfj = XPDFJ->new(debuginfo => $opt_d, verbose => $opt_v);
$xpdfj->parsefile($file, outfile => $outfile);
