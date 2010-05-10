<?xml version="1.0" encoding="x-sjis-cp932"?>
<!-- 
toc.inc : �ڎ��}�N��
2004 <nakajima@netstock.co.jp>
���A�E�g���C����ڎ�������B
����{�p�^�[���͎��̂悤�ɂȂ�B
<do file="stddefs.inc"/>
<do file="toc.inc"/>
<BODY>
�c�{���̓��e�c
</BODY>
<BODY page="1">
�c�\���Ȃǂ̓��e�c
<TOC/>
</BODY>
-->

<do>

<!--
  �A�E�g���C�������q�̔z��Q�Ƃɕϊ�����T�u���[�`��
-->
<eval>
  sub outlinetree2array {
    my($tree, $level) = @_;
    $level += 0;
    my $maxlevel = $level;
    my $result = [];
    for my $elm(@$tree) {
      my($title, $page, $x, $y, $child) = @$elm;
      push @$result, [$level, $title, $page, $x, $y] if $title ne '';
      if( ref($child) eq 'ARRAY' ) {
        my($carray, $clevel) = outlinetree2array($child, $level + 1);
        push @$result, @$carray;
        $maxlevel = $clevel if $clevel > $maxlevel;
      }
    }
    ($result, $maxlevel);
  }
</eval>

<!--
  <TOC>�F�A�E�g���C������ڎ����쐬���A���̒i�����X�g��Ԃ�
  �����Flevelindent=���x�����̃C���f���g�ʁi�ȗ����l10�j
        endindent=�\��̍s���C���f���g�i�ȗ����l60�j
        space=�\��ƃy�[�W�ԍ��̊Ԃ̍ŏ��󔒃T�C�Y�i�ȗ����l30�j
        dot=�\��ƃy�[�W�ԍ��̊Ԃ𖄂߂镶����i�ȗ����l"�d"�j
        ��space��endindent��菬���Ȓl���w�肷�邱��
  ���e�F�����Ƃ��ĉ���
-->
<def tag="TOC" contentsmode="arg" levelindent="10" endindent="60" 
  space="30" dot="�d">
  <eval>
    $Args{_indent1} = $Args{levelindent};
    $Args{_indent2} = $Args{levelindent} * 2;
    $Args{_indent3} = $Args{levelindent} * 3;
  </eval>
  <do caller="$PStyle{default}">
    <clone setvar="$PStyleHash{TOC0}" align="b" beginindent="0" 
      endindent="$Args{endindent}"/>
    <clone setvar="$PStyleHash{TOC1}" align="b" beginindent="$Args{_indent1}"
      endindent="$Args{endindent}"/>
    <clone setvar="$PStyleHash{TOC2}" align="b" beginindent="$Args{_indent2}"
      endindent="$Args{endindent}"/>
    <clone setvar="$PStyleHash{TOC3}" align="b" beginindent="$Args{_indent3}"
      endindent="$Args{endindent}"/>
  </do>
  <do caller="$TStyle{default}">
    <clone setvar="$TStyleHash{TOC0}" bold="1"/>
    <clone setvar="$TStyleHash{TOC1}"/>
    <clone setvar="$TStyleHash{TOC2}"/>
    <clone setvar="$TStyleHash{TOC3}"/>
  </do>
  <eval>
    ($Args{_array}, $Args{_maxlevel}) = outlinetree2array($Doc->outlinetree);
    if( $Args{_maxlevel} > 1 ) {
      $PStyleHash{TOC0}{preskip} = $Doc{Fontsize} * 2;
      $PStyleHash{TOC0}{postnobreak} = 1;
    } else {
      delete $PStyleHash{TOC0}{preskip};
      delete $PStyleHash{TOC0}{postnobreak};
    }
    $Args{_spaceglue} = [$Args{space} / $TStyle{default}{fontsize}, 
      $Args{space} / $TStyle{default}{fontsize}, 1000, 3];
    $Args{_spacestyle} = {filltext => $Args{dot}};
  </eval>
  <for setvar="$Args{_elm}" eval="$Args{_array}">
    <eval>
      @Args{qw(_level _title _page _x _y)} = @{$Args{_elm}};
      $Args{_pagenum} = $Args{_page}->pagenum;
      $Args{_name} = "TOC$Args{_level}";
      $Args{_pstyle} = $PStyleHash{$Args{_name}};
      $Args{_tstyle} = $TStyleHash{$Args{_name}};
      $Args{_altstyle} = {align => [qw(W e)], endindent => 0};
      $Args{_linkstyle} = {withbox => 'n', 
        withboxstyle => {link => [@Args{qw(_page _x _y)}]}};
    </eval>
    <clone setvar="$Args{_ttstyle}" caller="$Args{_tstyle}" 
      style="$Args{_linkstyle}"/>
    <Text setvar="$Args{_title}" style="$Args{_ttstyle}" texts="$Args{_title}"/>
    <Text setvar="$Args{_page}" style="$Args{_tstyle}" texts="$Args{_pagenum}"/>
    <return>
      <Paragraph style="$Args{_pstyle}">
        <text>
          <Text style="$Args{_tstyle}">
            <texts>$Args{_title}</texts>
            <texts><Null style="$Args{_altstyle}"/></texts>
            <texts>
              <Space size="0" glue="$Args{_spaceglue}" 
                style="$Args{_spacestyle}"/>
            </texts>
            <texts>$Args{_page}</texts>
          </Text>
        </text>
      </Paragraph>
    </return>
  </for>
</def>

</do>