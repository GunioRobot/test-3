<do>

<do file="stddefs.inc" pagewidth="842" pageheight="595" margin="60" 
	fontfiles="stdfontsV.inc, stdfontsH.inc" 
	boldmincho="dfgoteb.ttc:0" boldgothic="dfgoteb.ttc:0"
	defaultfont="gothic_helvetica"
	fontsize="25" labelsize="25" linefeed="120%"
/>

<eval>
	$Font{normal} = $FontH{gothic_helvetica};
	$Font{bold} = $FontH{gothic_helvetica_bold};
	$Font{tate} = $FontV{gothic_helvetica};
</eval>

<clone setvar="$PStyle{default}" caller="$PStyle{default}" preskip="5" postskip="5"/>

<PStyle setvar="$PStyle{highline}" align="w" linefeed="180%" preskip="5" postskip="5"/>
<TStyle setvar="$TStyle{tate}" font="$Font{tate}" fontsize="25"/>
<TStyle setvar="$TStyle{withnote}" font="$Font{normal}" fontsize="20"/>
<TStyle setvar="$TStyle{twithnote}" font="$Font{tate}" fontsize="12.5"/>
<TStyle setvar="$TStyle{small}" font="$Font{normal}" fontsize="20"/>
<PStyle setvar="$PStyle{small}" align="w" linefeed="120%" preskip="5" postskip="5"/>
<TStyle setvar="$TStyle{bigtitle}" font="$Font{bold}" fontsize="40"/>
<TStyle setvar="$TStyle{whitebigtitle}" font="$Font{bold}" fontsize="40" shapestyle="fillcolor:1"/>
<PStyle setvar="$PStyle{bigtitle}" align="m" linefeed="120%" preskip="20" postskip="20"/>
<TStyle setvar="$TStyle{smalltitle}" font="$Font{bold}" fontsize="30"/>
<TStyle setvar="$TStyle{whitesmalltitle}" font="$Font{bold}" fontsize="30" shapestyle="fillcolor:1"/>
<PStyle setvar="$PStyle{smalltitle}" align="m" linefeed="120%" preskip="20" postskip="20"/>
<TStyle setvar="$TStyle{pagetitle}" font="$Font{bold}" fontsize="30"/>
<PStyle setvar="$PStyle{pagetitle}" align="b" linefeed="120%" preskip="20" postskip="20"/>
<TStyle setvar="$TStyle{note}" font="$Font{normal}" fontsize="20"/>
<PStyle setvar="$PStyle{note}" align="w" linefeed="120%" preskip="5" postskip="5" beginpadding="30"/>

</do>
