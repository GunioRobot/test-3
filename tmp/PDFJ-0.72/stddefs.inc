<?xml version="1.0" encoding="x-sjis-cp932"?>
<!-- 
stddefs.inc : XPDFJの標準マクロ
2003 <nakajima@netstock.co.jp>
文書の先頭で、
 <do file="stddefs.inc" pagewidth="100" pageheight="200" margin="20"
 fontfiles="stdfontsV.inc, stdfontsH.inc"/>
のように呼び出す。（引数については下記参照）
Docオブジェクトはこのマクロの中で作成される。
-->
<do>

<!-- XPDFJのバージョンをチェック -->
<require XPDFJ="0.12"/>

<!-- 引数とデフォルト値にもとづいて%Docをセット -->
<eval>
	$Doc{Version} = $Args{version} || 1.3;
	$Doc{Pagewidth} = $Args{pagewidth} || 595;
	$Doc{Pageheight} = $Args{pageheight} || 842;
	$Doc{Leftmargin} = $Args{leftmargin} || $Args{margin} || 72;
	$Doc{Rightmargin} = $Args{rightmargin} || $Args{margin} || 72;
	$Doc{Topmargin} = $Args{topmargin} || $Args{margin} || 72;
	$Doc{Bottommargin} = $Args{bottommargin} || $Args{margin} || 72;
	$Doc{Fontsize} = $Args{fontsize} || 10;
	$Doc{Labelsize} = $Args{labelsize} || $Doc{Fontsize};
	$Doc{Linefeed} = $Args{linefeed} || '150%';
	$Doc{Bodywidth} = $Doc{Pagewidth} - $Doc{Leftmargin} - $Doc{Rightmargin};
	$Doc{Bodyleft} = $Doc{Leftmargin}; 
	$Doc{Bodyright} = $Doc{Pagewidth} - $Doc{Rightmargin}; 
	$Doc{Bodytop} = $Doc{Pageheight} - $Doc{Topmargin};
	$Doc{Bodyheight} = $Doc{Pageheight} - $Doc{Topmargin} - $Doc{Bottommargin};
</eval>

<!-- Docオブジェクトの作成 -->
<Doc version="$Doc{Version}" pagewidth="$Doc{Pagewidth}" 
	pageheight="$Doc{Pageheight}"/>

<!-- fontfilesの指定にもとづいてフォント定義ファイルを読み込む -->
<eval>
	$Args{fontfiles} ||= 'stdfontsH.inc';
	if( $Args{fontfiles} =~ /,/ ) {
		$Args{fontfiles} = [split(/\s*,\s*/, $Args{fontfiles})];
	}
</eval>
<for setvar="$_file" eval="$Args{fontfiles}">
  <do file="$_file"/>
</for>

<!-- 
  normalとdefaultのテキスト・段落スタイルを定義 
  defaultは<UL><OL><TD>などの中では変化する
-->
<TStyle setvar="$TStyle{normal}" font="$Font{default}" 
fontsize="$Doc{Fontsize}"/>
<PStyle setvar="$PStyle{normal}" size="$Doc{Bodywidth}" align="w" 
linefeed="$Doc{Linefeed}"/>
<eval>$TStyle{default} = $TStyle{normal}</eval>
<eval>$PStyle{default} = $PStyle{normal}</eval>

<!-- 以下、タグ定義 -->

<!--
  <T>：テキストオブジェクトを返す
  属性：tstyle=テキストスタイルオブジェクトまたはスタイル文字列
  内容：テキスト（改行はNewLineに）
-->
<def tag="T" contentsname="text" contentsmode="autonl" tstyle="">
  <do unless="$Args{tstyle}" result="null">
    <TStyle setvar="$Args{tstyle}"/>
  </do>
  <Text style="$Args{tstyle}">
    <texts>$Args{text}</texts>
  </Text>
</def>

<!--
  <S>：スタイルを指定してテキストオブジェクトを得る
  属性：テキストスタイルの引数をそのまま与える（例：italic="1" color="#ff0000"）
        colorはshapestyleのfillcolorとして扱われる
  内容：テキスト（改行はNewLineに）
-->
<def tag="S" contentsname="text" contentsmode="autonl" attributesname="attr">
  <eval>
    if( $Args{attr}{color} ) {
      my $color = delete $Args{attr}{color};
      $Args{attr}{shapestyle} = {fillcolor => $color};
    }
  </eval>
  <Text>
    <texts>$Args{text}</texts>
    <style><TStyle attributes="$Args{attr}"/></style>
  </Text>
</def>

<!--
  <YEN>：整数値を円マーク付きカンマ区切りの文字列にして返す
  属性：なし
  内容：テキスト（整数値であること）
-->
<def tag="YEN" contentsname="number" contentsmode="text">
  <reval>'￥'.addcomma($Args{number}[0])</reval>
</def>

<!--
  <P>：段落オブジェクトを返す
  属性：pstyle=段落スタイルオブジェクトまたはスタイル文字列
               $PStyle{default}をベースにcloneされる
        align=left、center、rightのいずれか。それぞれ段落スタイルのb、m、eに
              変換される
        tstyle=テキストスタイルオブジェクトまたはスタイル文字列（内容をテキスト
               オブジェクト化するときに使われる）
  内容：テキスト（改行はNewLineに）
-->
<def tag="P" contentsname="text" contentsmode="autonl" pstyle="" 
tstyle="">
  <eval>
    if( $Args{align} ) {
      $Args{align} = 
        $Args{align} eq 'left' ? 'b' :
        $Args{align} eq 'center' ? 'm' :
        $Args{align} eq 'right' ? 'e' :
        'w';
    }
    $Args{tstyle} ||= $TStyle{default};
  </eval>
  <do if="$Args{pstyle}" result="null">
    <clone setvar="$Args{pstyle}" caller="$PStyle{default}" 
    style="$Args{pstyle}"/>
  </do>
  <eval>$Args{pstyle} ||= $PStyle{default}</eval>
  <do if="$Args{align}" result="null">
    <clone setvar="$Args{pstyle}" caller="$Args{pstyle}" align="$Args{align}"/>
  </do>
  <Paragraph style="$Args{pstyle}"><text><Text style="$Args{tstyle}">
  <texts>$Args{text}</texts></Text></text></Paragraph>
</def>

<!--
  <UL>：箇条書き環境
  引数：pstyle=段落スタイルオブジェクトまたはスタイル文字列
               （省略すると$PStyle{default}）
        label=ラベル文字列（省略すると「・」）
        labelsize=ラベルサイズ（省略すると$Doc{Labelsize}）
  内容：<LI>または<P>の並び
-->
<def tag="UL" contentsname="contents" contentsmode="raw" 
label="・" labelsize="$Doc{Labelsize}" pstyle="$PStyle{default}">
  <local setvar="$PStyle{default}"/>
  <do result="null">
    <eval>
      $_beginpadding = $Args{list_indent} + 0;
      $_indent = $Args{list_indent} + $Args{labelsize};
      ++$List{level};
    </eval>
    <clone setvar="$PStyle{default}" caller="$Args{pstyle}" 
    beginpadding="$_indent"/>
    <clone setvar="$_pstyle" caller="$Args{pstyle}" 
    labelsize="$Args{labelsize}" labeltext="$Args{label}" 
    beginpadding="$_beginpadding"/>
  </do>
  <do contents="$Args{contents}" list_indent="$_indent" list_pstyle="$_pstyle"/>
  <eval>--$List{level}</eval>
</def>

<!--
  <OL>：番号付き箇条書き環境
  引数：pstyle=段落スタイルオブジェクトまたはスタイル文字列
               （省略すると$PStyle{default}）
        label=ラベル初期値（省略すると1）
              ※今のところ、指定できるのは半角の英数字のみ
        prelabel=ラベルの前置文字列
        postlabel=ラベルの後置文字列（省略すると「.」）
        labelsize=ラベルサイズ（省略すると$Doc{Labelsize}）
  内容：<LI>または<P>の並び
-->
<def tag="OL" contentsname="contents" contentsmode="raw"
label="1" prelabel="" postlabel="." labelsize="$Doc{Labelsize}" 
pstyle="$PStyle{default}">
  <local setvar="$PStyle{default}"/>
  <do result="null">
    <eval>
      ++$List{level};
      $List{counter}[$List{level}] = $Args{label};
      $_beginpadding = $Args{list_indent} + 0;
      $_indent = $Args{list_indent} + $Args{labelsize};
    </eval>
    <clone setvar="$PStyle{default}" caller="$Args{pstyle}" 
    beginpadding="$_indent"/>
    <clone setvar="$_pstyle" caller="$Args{pstyle}" 
    labelsize="$Args{labelsize}" beginpadding="$_beginpadding"/>
  </do>
  <do contents="$Args{contents}" list_indent="$_indent" 
  list_pstyle="$_pstyle" list_prelabel="$Args{prelabel}" 
  list_postlabel="$Args{postlabel}"/>
  <eval>
    $List{counter}[$List{level}] = undef;
    --$List{level};
  </eval>
</def>

<!--
  <LI>：箇条書き段落
  引数：tstyle=テキストスタイルオブジェクトまたはスタイル文字列
               （省略すると$TStyle{default}）
  内容：テキスト（改行はNewLineに）
-->
<def tag="LI" contentsname="text" contentsmode="autonl" 
tstyle="$TStyle{default}">
  <eval>$_pstyle = $Args{list_pstyle}</eval>
  <do if="defined $List{counter}[$List{level}]" result="null">
    <eval>
      $_counter = $List{counter}[$List{level}]++;
      $_prelabel = $Args{list_prelabel} || '';
      $_postlabel = $Args{list_postlabel} || '';
    </eval>
    <clone setvar="$_pstyle" caller="$_pstyle">
      <labeltext>
        <Text style="$Args{tstyle}">
          <texts>$_prelabel</texts>
          <texts>$_counter</texts>
          <texts>$_postlabel</texts>
        </Text>
      </labeltext>
    </clone>
  </do>
  <Paragraph style="$_pstyle"><text><Text style="$Args{tstyle}">
  <texts>$Args{text}</texts></Text></text></Paragraph>
</def>

<!--
  <HR>：横線のみを含むブロックオブジェクトを返す
  引数：width=横幅（省略すると「100%」）
              （%指定すると現在の$PStyle{default}{size}に対する割合）
        size=線幅（省略すると0.25）
        color=色（省略すると黒）
        align=left、center、rightのいずれか（省略するとcenter）
  内容：なし
-->
<def tag="HR" width="100%" size="0.25" color="0" align="center">
  <eval>
    $_fullwidth = $PStyle{default}{size};
    $_width = $Args{width} =~ /^\d+%$/ ? $Args{width} * $_fullwidth / 100 :
      $Args{width};
    $Args{align} = 
      $Args{align} eq 'left' ? 'l' :
      $Args{align} eq 'center' ? 'c' :
      $Args{align} eq 'right' ? 'r' : 'c';
  </eval>
  <Block direction="V">
    <style><BStyle width="$_fullwidth" align="$Args{align}"/></style>
    <objects>
      <Shape>
        <call>
          <line x="0" y="0" w="$_width" h="0">
            <style>
              <SStyle linewidth="$Args{size}">
                <strokecolor><Color value="$Args{color}"/></strokecolor>
              </SStyle>
            </style>
          </line>
        </call>
      </Shape>
    </objects>
  </Block>
</def>

<!--
  <TABLE>：表のブロックオブジェクトを返す
  引数：cellwidth=セル幅（省略すると「200」）
            （カンマ区切りで各セルの幅を指定。セル数のほうが多いと最後の値が
            繰り返し使われる。%指定すると現在の$PStyle{default}{size}に対する
            割合）
        cellpadding=セル内余白
        cellbox=セルボックス（PDFJのboxのspec指定）
        cellboxstyle=セルボックススタイル（PDFJのboxのstyle指定）
            （省略すると「linewidth: 0.25」）
        tablebox=表ボックス（PDFJのboxのspec指定）
        tableboxstyle=表ボックススタイル（PDFJのboxのstyle指定）
            （省略すると「linewidth: 0.25」）
  内容：<TR>の並び
  ※今のところ、横書きにのみ対応
-->
<def tag="TABLE" contentsname="contents" contentsmode="raw" 
cellwidth="200" cellpadding="0" cellbox="" 
cellboxstyle="linewidth: 0.25" tablebox="" tableboxstyle="linewidth: 0.25">
  <eval>
    ++$Table{level};
    $_fullwidth = $PStyle{default}{size};
    $_cellwidth = [split(/\s*,\s*/, $Args{cellwidth})];
    grep {$_ = $_fullwidth * $_ / 100 if /^\d+%$/} @$_cellwidth;
  </eval>
  <Block direction="V">
    <style><BStyle withbox="$Args{tablebox}" withboxstyle="$Args{tableboxstyle}"/></style>
    <objects>
      <do contents="$Args{contents}" cellwidth="$_cellwidth" 
      cellpadding="$Args{cellpadding}" cellbox="$Args{cellbox}" 
      cellboxstyle="$Args{cellboxstyle}"/>
    </objects>
  </Block>
  <eval>--$Table{level}</eval>
</def>

<!--
  <TR>：表の行のブロックオブジェクトを返す
  引数：cellpadding=セル内余白
        cellbox=セルボックス（PDFJのboxのspec指定）
        cellboxstyle=セルボックススタイル（PDFJのboxのstyle指定）
        ※いずれも省略すると<TABLE>で指定した値
  内容：<TD>の並び
-->
<def tag="TR" contentsname="contents" contentsmode="raw">
  <eval>$Table{colnum}[$Table{level}] = 0;</eval>
  <Block direction="H">
    <style><BStyle adjust="1"/></style>
    <objects>
      <do contents="$Args{contents}" cellpadding="$Args{cellpadding}" 
      cellbox="$Args{cellbox}" cellboxstyle="$Args{cellboxstyle}"/>
    </objects>
  </Block>
</def>

<!--
  <TD>：表のセルのブロックオブジェクトを返す
  引数：cellpadding=セル内余白
        cellbox=セルボックス（PDFJのboxのspec指定）
        cellboxstyle=セルボックススタイル（PDFJのboxのstyle指定）
        ※いずれも省略すると<TABLE>あるいは<TR>で指定した値
        palign=left、center、right。それぞれb、m、eとして段落のalignに
        balign=left、center、right。それぞれl、c、rとしてブロックのalignに
  内容：テキストまたはオブジェクトの並び
        （テキストの場合は段落オブジェクト化される）
-->
<def tag="TD" pstyle="" contentsname="contents" contentsmode="raw">
  <local setvar="$PStyle{default}"/>
  <eval>
    $Args{tstyle} ||= $TStyle{default};
    my $j = $Table{colnum}[$Table{level}];
    $j = @{$Args{cellwidth}} - 1 if $j >= @{$Args{cellwidth}};
    $Args{_width} = $Args{cellwidth}->[$j];
    $Args{_size} = $Args{_width} - $Args{cellpadding} * 2;
    $Args{palign} = 
      $Args{align} eq 'left' ? 'b' :
      $Args{align} eq 'center' ? 'm' :
      $Args{align} eq 'right' ? 'e' :
      'w';
    $Args{balign} = 
      $Args{align} eq 'left' ? 'l' :
      $Args{align} eq 'center' ? 'c' :
      $Args{align} eq 'right' ? 'r' :
      'l';
    $_istext = istext($Args{contents}[1]);
  </eval>
  <do result="null">
    <clone setvar="$PStyle{default}" caller="$PStyle{default}" 
    size="$Args{_size}" align="$Args{palign}"/>
    <do if="$Args{pstyle}" result="null">
      <do unless="ref($Args{pstyle})">
        <PStyle setvar="$Args{pstyle}" style="$Args{pstyle}"/>
      </do>
      <clone setvar="$Args{pstyle}" caller="$PStyle{default}" 
      style="$Args{pstyle}"/>
    </do>
    <eval>$Args{pstyle} ||= $PStyle{default}</eval>
    <BStyle setvar="$Args{_style}" width="$Args{_width}" 
    padding="$Args{cellpadding}" withbox="$Args{cellbox}" 
    withboxstyle="$Args{cellboxstyle}" align="$Args{balign}"/>
  </do>
  <do if="$_istext">
    <Block direction="V" style="$Args{_style}">
      <objects>
        <Paragraph style="$Args{pstyle}"><text><Text style="$Args{tstyle}">
        <texts><do contents="$Args{contents}" withtext="autonl"/></texts></Text></text></Paragraph>
      </objects>
    </Block>
  </do>
  <do unless="$_istext">
    <do setvar="$_coocked" contents="$Args{contents}" result="null"/>
    <do if="!ref($_coocked) || ref($_coocked) eq 'PDFJ::Text' || !ref($_coocked->[0])" result="null">
      <Paragraph setvar="$_coocked" style="$Args{pstyle}">
      <text><Text style="$Args{tstyle}"><texts>$_coocked</texts></Text></text>
      </Paragraph>
    </do>
    <Block direction="V" style="$Args{_style}">
      <objects>$_coocked</objects> 
    </Block>
  </do>
  <eval>++$Table{colnum}[$Table{level}]</eval>
</def>

<!--
  <TH>：<TD align="center">
-->
<alias tag="TH" aliasof="TD" align="center"/>

<!--
  <BR>：<NewLine>
-->
<alias tag="BR" aliasof="NewLine"/>

</do>
