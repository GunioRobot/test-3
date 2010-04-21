<!-- 
stdfontsH.inc : standard font definitions for XPDFJ 
2003 <nakajima@netstock.co.jp>
-->
<do>

<eval>
	$Args{normalmincho} ||= 'Ryumin-Light';
	$Args{boldmincho} ||= 'Ryumin-Light';
	$Args{normalgothic} ||= 'GothicBBB-Medium';
	$Args{boldgothic} ||= 'GothicBBB-Medium';
	
	$Args{normalminchoenc} ||= 'UniJIS-UCS2-HW-H';
	$Args{boldminchoenc} ||= 'UniJIS-UCS2-HW-H';
	$Args{normalgothicenc} ||= 'UniJIS-UCS2-HW-H';
	$Args{boldgothicenc} ||= 'UniJIS-UCS2-HW-H';

	for my $name(qw(normalminchoenc boldminchoenc normalgothicenc boldgothicenc)) {
		$Args{$name} =~ s/-[HV]$/-H/ or $Args{$name} =~ s/$/-H/;
	}
</eval>

<new_font setvar="$FontH{mincho}" basefont="$Args{normalmincho}" 
	encoding="$Args{normalminchoenc}"/>
<new_font setvar="$FontH{mincho_times}" basefont="$Args{normalmincho}" 
	encoding="$Args{normalminchoenc}" abasefont="Times-Roman" 
	aencoding="WinAnsiEncoding"/>
<new_font setvar="$FontH{mincho_times_italic}" basefont="$Args{normalmincho}" 
	encoding="$Args{normalminchoenc}" abasefont="Times-Italic" 
	aencoding="WinAnsiEncoding"/>
<new_font setvar="$FontH{mincho_times_bold}" basefont="$Args{boldmincho}" 
	encoding="$Args{boldminchoenc}" abasefont="Times-Bold" 
	aencoding="WinAnsiEncoding"/>
<new_font setvar="$FontH{mincho_times_bolditalic}" basefont="$Args{boldmincho}" 
	encoding="$Args{boldminchoenc}" abasefont="Times-BoldItalic" 
	aencoding="WinAnsiEncoding"/>

<italic base="$FontH{mincho_times}" decorated="$FontH{mincho_times_italic}"/>
<italic base="$FontH{mincho_times_bold}" decorated="$FontH{mincho_times_bolditalic}"/>
<bold base="$FontH{mincho_times}" decorated="$FontH{mincho_times_bold}"/>
<bold base="$FontH{mincho_times_italic}" decorated="$FontH{mincho_times_bolditalic}"/>

<new_font setvar="$FontH{gothic}" basefont="$Args{normalgothic}" 
	encoding="$Args{normalgothicenc}"/>
<new_font setvar="$FontH{gothic_helvetica}" basefont="$Args{normalgothic}" 
	encoding="$Args{normalgothicenc}" abasefont="Helvetica" 
	aencoding="WinAnsiEncoding"/>
<new_font setvar="$FontH{gothic_helvetica_oblique}" basefont="$Args{normalgothic}" 
	encoding="$Args{normalgothicenc}" abasefont="Helvetica-Oblique" 
	aencoding="WinAnsiEncoding"/>
<new_font setvar="$FontH{gothic_helvetica_bold}" basefont="$Args{boldgothic}" 
	encoding="$Args{boldgothicenc}" abasefont="Helvetica-Bold" 
	aencoding="WinAnsiEncoding"/>
<new_font setvar="$FontH{gothic_helvetica_boldoblique}" basefont="$Args{boldgothic}" 
	encoding="$Args{boldgothicenc}" abasefont="Helvetica-BoldOblique" 
	aencoding="WinAnsiEncoding"/>

<italic base="$FontH{gothic_helvetica}" decorated="$FontH{gothic_helvetica_oblique}"/>
<italic base="$FontH{gothic_helvetica_bold}" decorated="$FontH{gothic_helvetica_boldoblique}"/>
<bold base="$FontH{gothic_helvetica}" decorated="$FontH{gothic_helvetica_bold}"/>
<bold base="$FontH{gothic_helvetica_oblique}" decorated="$FontH{gothic_helvetica_boldoblique}"/>

<eval>
	my $name = $Args{defaultfont} || 'mincho_times';
	die qq(missing \$FontH{$name}) unless $FontH{$name};
	$Font{default} = $FontH{$name};
</eval>

</do>
