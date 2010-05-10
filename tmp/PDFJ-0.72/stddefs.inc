<?xml version="1.0" encoding="x-sjis-cp932"?>
<!-- 
stddefs.inc : XPDFJ�̕W���}�N��
2003 <nakajima@netstock.co.jp>
�����̐擪�ŁA
 <do file="stddefs.inc" pagewidth="100" pageheight="200" margin="20"
 fontfiles="stdfontsV.inc, stdfontsH.inc"/>
�̂悤�ɌĂяo���B�i�����ɂ��Ă͉��L�Q�Ɓj
Doc�I�u�W�F�N�g�͂��̃}�N���̒��ō쐬�����B
-->
<do>

<!-- XPDFJ�̃o�[�W�������`�F�b�N -->
<require XPDFJ="0.12"/>

<!-- �����ƃf�t�H���g�l�ɂ��ƂÂ���%Doc���Z�b�g -->
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

<!-- Doc�I�u�W�F�N�g�̍쐬 -->
<Doc version="$Doc{Version}" pagewidth="$Doc{Pagewidth}" 
	pageheight="$Doc{Pageheight}"/>

<!-- fontfiles�̎w��ɂ��ƂÂ��ăt�H���g��`�t�@�C����ǂݍ��� -->
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
  normal��default�̃e�L�X�g�E�i���X�^�C�����` 
  default��<UL><OL><TD>�Ȃǂ̒��ł͕ω�����
-->
<TStyle setvar="$TStyle{normal}" font="$Font{default}" 
fontsize="$Doc{Fontsize}"/>
<PStyle setvar="$PStyle{normal}" size="$Doc{Bodywidth}" align="w" 
linefeed="$Doc{Linefeed}"/>
<eval>$TStyle{default} = $TStyle{normal}</eval>
<eval>$PStyle{default} = $PStyle{normal}</eval>

<!-- �ȉ��A�^�O��` -->

<!--
  <T>�F�e�L�X�g�I�u�W�F�N�g��Ԃ�
  �����Ftstyle=�e�L�X�g�X�^�C���I�u�W�F�N�g�܂��̓X�^�C��������
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
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
  <S>�F�X�^�C�����w�肵�ăe�L�X�g�I�u�W�F�N�g�𓾂�
  �����F�e�L�X�g�X�^�C���̈��������̂܂ܗ^����i��Fitalic="1" color="#ff0000"�j
        color��shapestyle��fillcolor�Ƃ��Ĉ�����
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
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
  <YEN>�F�����l���~�}�[�N�t���J���}��؂�̕�����ɂ��ĕԂ�
  �����F�Ȃ�
  ���e�F�e�L�X�g�i�����l�ł��邱�Ɓj
-->
<def tag="YEN" contentsname="number" contentsmode="text">
  <reval>'��'.addcomma($Args{number}[0])</reval>
</def>

<!--
  <P>�F�i���I�u�W�F�N�g��Ԃ�
  �����Fpstyle=�i���X�^�C���I�u�W�F�N�g�܂��̓X�^�C��������
               $PStyle{default}���x�[�X��clone�����
        align=left�Acenter�Aright�̂����ꂩ�B���ꂼ��i���X�^�C����b�Am�Ae��
              �ϊ������
        tstyle=�e�L�X�g�X�^�C���I�u�W�F�N�g�܂��̓X�^�C��������i���e���e�L�X�g
               �I�u�W�F�N�g������Ƃ��Ɏg����j
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
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
  <UL>�F�ӏ�������
  �����Fpstyle=�i���X�^�C���I�u�W�F�N�g�܂��̓X�^�C��������
               �i�ȗ������$PStyle{default}�j
        label=���x��������i�ȗ�����Ɓu�E�v�j
        labelsize=���x���T�C�Y�i�ȗ������$Doc{Labelsize}�j
  ���e�F<LI>�܂���<P>�̕���
-->
<def tag="UL" contentsname="contents" contentsmode="raw" 
label="�E" labelsize="$Doc{Labelsize}" pstyle="$PStyle{default}">
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
  <OL>�F�ԍ��t���ӏ�������
  �����Fpstyle=�i���X�^�C���I�u�W�F�N�g�܂��̓X�^�C��������
               �i�ȗ������$PStyle{default}�j
        label=���x�������l�i�ȗ������1�j
              �����̂Ƃ���A�w��ł���͔̂��p�̉p�����̂�
        prelabel=���x���̑O�u������
        postlabel=���x���̌�u������i�ȗ�����Ɓu.�v�j
        labelsize=���x���T�C�Y�i�ȗ������$Doc{Labelsize}�j
  ���e�F<LI>�܂���<P>�̕���
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
  <LI>�F�ӏ������i��
  �����Ftstyle=�e�L�X�g�X�^�C���I�u�W�F�N�g�܂��̓X�^�C��������
               �i�ȗ������$TStyle{default}�j
  ���e�F�e�L�X�g�i���s��NewLine�Ɂj
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
  <HR>�F�����݂̂��܂ރu���b�N�I�u�W�F�N�g��Ԃ�
  �����Fwidth=�����i�ȗ�����Ɓu100%�v�j
              �i%�w�肷��ƌ��݂�$PStyle{default}{size}�ɑ΂��銄���j
        size=�����i�ȗ������0.25�j
        color=�F�i�ȗ�����ƍ��j
        align=left�Acenter�Aright�̂����ꂩ�i�ȗ������center�j
  ���e�F�Ȃ�
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
  <TABLE>�F�\�̃u���b�N�I�u�W�F�N�g��Ԃ�
  �����Fcellwidth=�Z�����i�ȗ�����Ɓu200�v�j
            �i�J���}��؂�Ŋe�Z���̕����w��B�Z�����̂ق��������ƍŌ�̒l��
            �J��Ԃ��g����B%�w�肷��ƌ��݂�$PStyle{default}{size}�ɑ΂���
            �����j
        cellpadding=�Z�����]��
        cellbox=�Z���{�b�N�X�iPDFJ��box��spec�w��j
        cellboxstyle=�Z���{�b�N�X�X�^�C���iPDFJ��box��style�w��j
            �i�ȗ�����Ɓulinewidth: 0.25�v�j
        tablebox=�\�{�b�N�X�iPDFJ��box��spec�w��j
        tableboxstyle=�\�{�b�N�X�X�^�C���iPDFJ��box��style�w��j
            �i�ȗ�����Ɓulinewidth: 0.25�v�j
  ���e�F<TR>�̕���
  �����̂Ƃ���A�������ɂ̂ݑΉ�
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
  <TR>�F�\�̍s�̃u���b�N�I�u�W�F�N�g��Ԃ�
  �����Fcellpadding=�Z�����]��
        cellbox=�Z���{�b�N�X�iPDFJ��box��spec�w��j
        cellboxstyle=�Z���{�b�N�X�X�^�C���iPDFJ��box��style�w��j
        ����������ȗ������<TABLE>�Ŏw�肵���l
  ���e�F<TD>�̕���
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
  <TD>�F�\�̃Z���̃u���b�N�I�u�W�F�N�g��Ԃ�
  �����Fcellpadding=�Z�����]��
        cellbox=�Z���{�b�N�X�iPDFJ��box��spec�w��j
        cellboxstyle=�Z���{�b�N�X�X�^�C���iPDFJ��box��style�w��j
        ����������ȗ������<TABLE>���邢��<TR>�Ŏw�肵���l
        palign=left�Acenter�Aright�B���ꂼ��b�Am�Ae�Ƃ��Ēi����align��
        balign=left�Acenter�Aright�B���ꂼ��l�Ac�Ar�Ƃ��ău���b�N��align��
  ���e�F�e�L�X�g�܂��̓I�u�W�F�N�g�̕���
        �i�e�L�X�g�̏ꍇ�͒i���I�u�W�F�N�g�������j
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
  <TH>�F<TD align="center">
-->
<alias tag="TH" aliasof="TD" align="center"/>

<!--
  <BR>�F<NewLine>
-->
<alias tag="BR" aliasof="NewLine"/>

</do>