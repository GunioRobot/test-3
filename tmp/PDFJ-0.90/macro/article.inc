<?xml version="1.0" encoding="x-sjis-cp932"?>
<!--
article.inc - �_���p�}�N��
2004 <nakajima@netstock.co.jp>
���̃}�N�����g�p�������e�̍\���́A���̂悤�ɂȂ�
<XPDFJ version="0.2">
<do file="article.inc"/>
<ARTICLE>
  <HEAD>
    <TITLE>,<ETITLE>,<AUTHOR>,<EAUTHOR>,<SUMMARY>,<ESUMMARY>�̕���
  </HEAD>
  <BODY>
    <SECTITLE>,<SUBSECTITLE>,<P>,<UL>,<OL>,<DL>,<TABLE>,<FOOTNOTE>,<FIG>,<REFERENCE>�̕���
  </BODY>
</ARTICLE>
<print file="�c"/>
</XPDFJ>
-->

<do>

<!--
�W���}�N���̑g�ݍ���
���T�C�Y�Ɨ]���͂����Œ���
�t�H���g�T�C�Y���ύX�ł��邪�A���o�����̃T�C�Y�Ƃ̃o�����X�������K�v
-->
<do file="stddefs.inc" 
	pagewidth="595" pageheight="842"
	leftmargin="42" rightmargin="42" topmargin="56" bottommargin="56"
	fontsize="9" labelsize="9"
	fontfiles="stdfontsH.inc" boldmincho="GothicBBB-Medium" 
/>

<!--
�ǉ��̃O���[�o���ϐ�
$Doc{Columngap} : �i�g�̒i��
$Doc{HeadBodySkip} : �w�b�_���Ɩ{�����̊Ԋu
-->
<eval>
	$Doc{Columngap} = 20;
	$Doc{HeadBodySkip} = 30;
	$Font{normal} = $FontH{mincho_times};
	$Font{bold} = $FontH{mincho_times_bold};
</eval>

<!--
�s�Ԃ̒���
150%�ł͂�����Ƃ��������Ȋ���������̂�
subsectitle�����킹�邱��
-->
<clone setvar="$PStyle{default}" caller="$PStyle{default}" linefeed="160%"/>

<!--
  <TITLE>�F�\��
  <ETITLE>�F�\��i�p���\�L�j
  <AUTHOR>�F����
  <EAUTHOR>�F���ҁi�p���\�L�j
  <SUMMARY>�F�T�v
  <ESUMMARY>�F�T�v�i�p���\�L�j
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
-->
<TStyle setvar="$TStyle{title}" font="$Font{bold}" fontsize="16"/>
<PStyle setvar="$PStyle{title}" size="$Doc{Bodywidth}" align="m" linefeed="120%" preskip="10" postskip="20"/>

<TStyle setvar="$TStyle{etitle}" font="$Font{bold}" fontsize="14"/>
<PStyle setvar="$PStyle{etitle}" size="$Doc{Bodywidth}" align="m" linefeed="120%" preskip="10" postskip="20"/>

<TStyle setvar="$TStyle{author}" font="$Font{normal}" fontsize="12"/>
<PStyle setvar="$PStyle{author}" size="$Doc{Bodywidth}" align="m" linefeed="120%" preskip="0" postskip="20"/>

<TStyle setvar="$TStyle{eauthor}" font="$Font{normal}" fontsize="12"/>
<PStyle setvar="$PStyle{eauthor}" size="$Doc{Bodywidth}" align="m" linefeed="120%" preskip="0" postskip="20"/>

<TStyle setvar="$TStyle{summary}" font="$Font{normal}" fontsize="8"/>
<PStyle setvar="$PStyle{summary}" size="$Doc{Bodywidth}" align="w" linefeed="130%" preskip="0" postskip="20" beginindent="40" endindent="40"/>

<TStyle setvar="$TStyle{esummary}" font="$Font{normal}" fontsize="8"/>
<PStyle setvar="$PStyle{esummary}" size="$Doc{Bodywidth}" align="w" linefeed="120%" preskip="0" postskip="20" beginindent="40" endindent="40"/>

<alias tag="TITLE" aliasof="_P" pstyle="$PStyle{title}" tstyle="$TStyle{title}"/>
<alias tag="ETITLE" aliasof="_P" pstyle="$PStyle{etitle}" tstyle="$TStyle{etitle}"/>

<alias tag="AUTHOR" aliasof="_P" pstyle="$PStyle{author}" tstyle="$TStyle{author}"/>
<alias tag="EAUTHOR" aliasof="_P" pstyle="$PStyle{eauthor}" tstyle="$TStyle{eauthor}"/>

<alias tag="SUMMARY" aliasof="_P" pstyle="$PStyle{summary}" tstyle="$TStyle{summary}"/>
<alias tag="ESUMMARY" aliasof="_P" pstyle="$PStyle{esummary}" tstyle="$TStyle{esummary}"/>

<!--
  <SECTITLE>�F�͌��o��
  <SUBSECTITLE>�F�ߌ��o��
  �����Flabel=���x���i�ȗ��j
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
  ��label�������ȗ�����ƁA�͌��o���́u1.�v�A�ߌ��o���́u1.1�v�̔ԍ����x���������I�ɕt���Blabel�������w�肷��Ɣԍ����x���͕t�����i�ԍ��̃J�E���g�A�b�v������Ȃ��j�w�肵�����x�����t��
-->
<TStyle setvar="$TStyle{sectitle}" font="$Font{bold}" fontsize="10"/>
<PStyle setvar="$PStyle{sectitle}" size="$Doc{Bodywidth}" align="b" linefeed="3.5" preskip="8.5" postskip="8.5" beginpadding="9" labelsize="15" postnobreak="1"/>

<TStyle setvar="$TStyle{subsectitle}" font="$Font{bold}" fontsize="9"/>
<PStyle setvar="$PStyle{subsectitle}" size="$Doc{Bodywidth}" align="b" linefeed="160%" beginpadding="9" labelsize="20" postnobreak="1"/>

<def tag="SECTITLE">
  <eval>
    if( $Args{label} eq '' ) {
      $SecNumber++;
      $SubSecNumber = 0;
      $_label = "$SecNumber.";
    } else {
      $_label = $Args{label};
    }
  </eval>
  <clone setvar="$_pstyle" caller="$PStyle{sectitle}">
    <labeltext><Text texts="$_label" style="$TStyle{sectitle}"/></labeltext>
  </clone>
  <return>
    <Paragraph style="$_pstyle">
      <text>
        <Text style="$TStyle{sectitle}">
          <texts><do withtext="autonl" contents="$Args{contents}"/></texts>
        </Text>
      </text>
    </Paragraph>
  </return>
</def>

<def tag="SUBSECTITLE">
  <eval>
    if( $Args{label} eq '' ) {
      $SubSecNumber++;
      $_label = "$SecNumber.$SubSecNumber";
    } else {
      $_label = $Args{label};
    }
  </eval>
  <clone setvar="$_pstyle" caller="$PStyle{subsectitle}">
    <labeltext><Text texts="$_label" style="$TStyle{subsectitle}"/></labeltext>
  </clone>
  <return>
    <Paragraph style="$_pstyle">
      <text>
        <Text style="$TStyle{subsectitle}">
          <texts><do withtext="autonl" contents="$Args{contents}"/></texts>
        </Text>
      </text>
    </Paragraph>
  </return>
</def>

<!--
  <FOOTNOTE>�F�r��
  �����Flabel=���x��
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
  ��float="e1"�Ńy�[�W�����ɔz�u�����ifloat="e"��FIG�̂���ɉ��Ɂj
-->
<TStyle setvar="$TStyle{footnote}" font="$Font{normal}" fontsize="8"/>
<PStyle setvar="$PStyle{footnote}" size="$Doc{Bodywidth}" align="w" linefeed="150%" labelsize="16" labelskip="8" float="e1"/>

<alias tag="FOOTNOTE" aliasof="_PL" pstyle="$PStyle{footnote}" tstyle="$TStyle{footnote}"/>

<!--
  <CAPTION>�F�}�\�̃L���v�V����
  <ECAPTION>�F�}�\�̃L���v�V�����i�p���\�L�j
  �����Flabel=���x��
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
-->
<TStyle setvar="$TStyle{caption}" font="$Font{normal}" fontsize="8"/>
<PStyle setvar="$PStyle{caption}" size="$Doc{Bodywidth}" align="m" linefeed="130%" preskip="3" postskip="3"/>

<TStyle setvar="$TStyle{ecaption}" font="$Font{normal}" fontsize="8"/>
<PStyle setvar="$PStyle{ecaption}" size="$Doc{Bodywidth}" align="m" linefeed="120%" preskip="3" postskip="3"/>

<alias tag="CAPTION" aliasof="_P" pstyle="$PStyle{caption}" tstyle="$TStyle{caption}"/>
<alias tag="ECAPTION" aliasof="_P" pstyle="$PStyle{ecaption}" tstyle="$TStyle{ecaption}"/>

<!--
  <FIG>�F�}�\
  �����Ffloat=�z�u�Bb:�㕔�Ae:�����Ah:���������\�Ȃ炻�̈ʒu�i�ȗ������b�j
  ���e�F<CAPTION>�A<ECAPTION>�܂��͔C�ӂ̃I�u�W�F�N�g
  �����e�̑S�̂���̃u���b�N�ƂȂ���float="b"�Ńy�[�W�㕔�ɔz�u�����
-->
<def tag="FIG" float="b">
  <return>
    <Block direction="V">
      <style>
        <BStyle nobreak="1" float="$Args{float}" align="c" 
        preskip="10" postskip="10"/>
      </style>
      <objects><do contents="$Args{contents}"/></objects>
    </Block>
  </return>
</def>

<!--
  <REFERENCE>�F�Q�l����
  �����Flabel=���x��
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
-->
<TStyle setvar="$TStyle{reference}" font="$Font{normal}" fontsize="8"/>
<PStyle setvar="$PStyle{reference}" size="$Doc{Bodywidth}" align="w" linefeed="150%" labelsize="16" labelskip="4"/>

<alias tag="REFERENCE" aliasof="_PL" pstyle="$PStyle{reference}" tstyle="$TStyle{reference}"/>

<!--
  <ARTICLE>�F�_���S��
  �����Fcol=�i���i1�܂���2�A�ȗ������2�j
  ���e�F<HEAD><BODY>
-->
<def tag="ARTICLE" col="2">
  <eval>
    die "'col' must be 1 or 2" unless $Args{col} == 1 || $Args{col} == 2;
    if( $Args{col} == 2 ) {
      $Doc{Columnwidth} = ($Doc{Bodywidth} - $Doc{Columngap}) / 2;
      $PStyle{sectitle}{size} = $Doc{Columnwidth};
      $PStyle{subsectitle}{size} = $Doc{Columnwidth};
      $PStyle{footnote}{size} = $Doc{Columnwidth};
      $PStyle{caption}{size} = $Doc{Columnwidth};
      $PStyle{ecaption}{size} = $Doc{Columnwidth};
      $PStyle{reference}{size} = $Doc{Columnwidth};
    }
  </eval>
  <do contents="$Args{contents}" col="$Args{col}"/>
  <height setvar="$Args{_headlen}" caller="$ArticleBlock{Head}"/>
  <eval>
    $_headlen = $Args{_headlen} + $Doc{HeadBodySkip};
    $_sizes = $Args{col} == 1 ? 
      [$Doc{Bodyheight} - $_headlen, $Doc{Bodyheight}] :
      [$Doc{Bodyheight} - $_headlen, $Doc{Bodyheight} - $_headlen,
      $Doc{Bodyheight}];
    $_count = 0;
  </eval>
  <new_page setvar="$_page"/>
  <eval>print "page",$_page->pagenum,"\n"</eval>
  <show page="$_page" caller="$ArticleBlock{Head}" 
  x="$Doc{Bodyleft}" y="$Doc{Bodytop}" align="tl"/>
  <break sizes="$_sizes" caller="$ArticleBlock{Body}">
    <call>
      <eval>
        $_count++;
        $_newpage = 0;
        if( ($Args{col} == 1 and $_count &gt; 1 ) ||
          ($Args{col} == 2 and $_count &gt; 2 and $_count % 2) ) {
          $_newpage = 1;
        }
        if( $Args{col} == 1 ) {
          $_x = $Doc{Bodyleft};
          $_y = $_count &lt;= 1 ? $Doc{Bodytop} - $_headlen : $Doc{Bodytop};
        } else {
          $_x = $_count % 2 ? $Doc{Bodyleft} : 
            $Doc{Bodyleft} + $Doc{Columnwidth} + $Doc{Columngap};
          $_y = $_count &lt;= 2 ? $Doc{Bodytop} - $_headlen : $Doc{Bodytop};
        }
      </eval>
      <do if="$_newpage">
        <new_page setvar="$_page" caller="$Doc"/>
        <eval>print "page",$_page->pagenum,"\n"</eval>
      </do>
      <show page="$_page" x="$_x" y="$_y" align="tl"/>
    </call>
  </break>
</def>

<!--
  <HEAD>�F�w�b�_��
  ���e�F<TITLE>,<ETITLE>,<AUTHOR>,<EAUTHOR>,<SUMMARY>,<ESUMMARY>�̕���
-->
<def tag="HEAD">
  <Block setvar="$ArticleBlock{Head}" direction="V">
    <style><BStyle/></style>
    <objects><do contents="$Args{contents}"/></objects>
  </Block>
  <height setvar="$Args{_height}" caller="$ArticleBlock{Head}"/>
  <eval>
    die "too long HEAD" 
      if $Args{_height} + $Doc{HeadBodySkip} &gt;= $Doc{Bodyheight};
  </eval>
</def>

<!--
  <BODY>�F�{����
  ���e�F<SECTITLE>,<SUBSECTITLE>,<P>,<UL>,<OL>,<DL>,<TABLE>,<FOOTNOTE>,<FIG>,<REFERENCE>�̕���
-->
<def tag="BODY">
  <do if="$Args{col} == 2">
    <clone setvar="$PStyle{default}" caller="$PStyle{default}" 
    size="$Doc{Columnwidth}"/>
  </do>
  <eval>$_width = $PStyle{default}{size}</eval>
  <Block setvar="$ArticleBlock{Body}" direction="V">
    <style><BStyle>
      <bfloatsep><BlockSkip skip="10"/></bfloatsep>
      <efloatsep><BlockSkip skip="10"/></efloatsep>
      <efloatsep>
        <Shape>
          <style><SStyle preskip="5" postskip="5" linewidth="0.25"/></style>
          <call><line x="0" y="0" w="$_width" h="0" style="s"/></call>
        </Shape>
      </efloatsep>
    </BStyle></style>
    <objects><do contents="$Args{contents}"/></objects>
  </Block>
</def>

</do>