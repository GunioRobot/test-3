# text2pdf.pl - simple PDFJ sample script
# 2002 <nakajima@netstock.co.jp>
# perl text2pdf.pl INFILE OUTFILE

# !!! Choice 'SJIS or 'EUC' !!!
use PDFJ 'SJIS';
#use PDFJ 'EUC';

use strict;

my($InFile, $OutFile) = @ARGV;

my @Pagesize = (595, 842); # A4 210mm x 297mm
my @Margin = (72, 72, 72, 72); # (left, right, top, bottom) 1inch
my $Fontsize = 10.5;
my $FontsizeHeader = 9;
my $FontsizeFooter = 9;
my $Font = "Ryumin-Light";
my $FontHeader = "GothicBBB-Medium";
my $FontFooter = "GothicBBB-Medium";
my $Encoding = "90ms-RKSJ-H";
my $HFont = "Times-Roman";
my $HFontHeader = "Helvetica";
my $HFontFooter = "Helvetica";
my $Linewidth = $Pagesize[0] - $Margin[0] - $Margin[1];
my $PageHeight = $Pagesize[1] - $Margin[2] - $Margin[3];
my @PosBody = ($Margin[0], $Pagesize[1] - $Margin[3]);
my @PosHeader = ($Margin[0], $Pagesize[1] - $Margin[3] + $Margin[2] / 2);
my @PosFooter = ($Margin[0], $Margin[3] / 2);
my $Tabwidth = 4;

my $doc = PDFJ::Doc->new(1.2, @Pagesize);
my $font = $doc->new_font($Font, $Encoding, $HFont);
my $font_header = $doc->new_font($FontHeader, $Encoding, $HFontHeader);
my $font_footer = $doc->new_font($FontFooter, $Encoding, $HFontFooter);
my $ts = TStyle(font => $font, fontsize => $Fontsize);
my $ts_header = TStyle(font => $font_header, fontsize => $FontsizeHeader);
my $ts_footer = TStyle(font => $font_footer, fontsize => $FontsizeFooter);
my $ps = PStyle(size => $Linewidth, align => 'w', linefeed => '150%');
my $ps_header = PStyle(size => $Linewidth, align => 'e', linefeed => '100%');
my $ps_footer = PStyle(size => $Linewidth, align => 'm', linefeed => '100%');

my @texts;
open F, $InFile or die;
while(<F>) {
	chomp;
	s/^\t+/' ' x (length($&)*$Tabwidth)/e;
	push @texts, Text($_, $ts), NewLine;
}
close F;
my $time = scalar(localtime);
for my $para(Paragraph(Text(\@texts, $ts), $ps)->break($PageHeight)) {
	my $page = $doc->new_page;
	$para->show($page, @PosBody);
	my $header = Paragraph(Text("$time  $InFile", $ts_header), 
		$ps_header);
	$header->show($page, @PosHeader);
	my $footer = Paragraph(Text($page->pagenum, $ts_footer), $ps_footer);
	$footer->show($page, @PosFooter);
}
$doc->print($OutFile);
