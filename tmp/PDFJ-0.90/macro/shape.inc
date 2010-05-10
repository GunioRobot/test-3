<?xml version="1.0" encoding="x-sjis-cp932"?>
<!-- 
  shape.inc : XPDFJ�̐}�`�}�N��
  2004 <nakajima@netstock.co.jp>
-->
<do>

<require version="0.21"/>

<!--
  <SHAPE>�F�}�`�iShape�I�u�W�F�N�g�j
  �����Fstyle=�}�`�X�^�C���i�ȗ��j
  ���e�F<LINE><BOX><CIRCLE><ELLIPSE><POLYGON><SHAPEOBJ>�Ȃǂ̕���
-->
<def tag="SHAPE" attributesname="attr">
  <Shape setvar="$Args{_shape}" attributes="$Args{attr}"/>
  <return>
    <do result="last" shape="$Args{_shape}" contents="$Args{contents}"/>
  </return>
</def>

<!--
  <LINE>�F����
  �����F�iPDFJ��line���\�b�h�̈������Q�Ɓj
  ���e�F�����Ƃ��ĉ���
-->
<def tag="LINE" contentsmode="arg" attributesname="attr">
  <return>
    <line caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <BOX>�F��`
  �����F�iPDFJ��box���\�b�h�̈������Q�Ɓj
  ���e�F�����Ƃ��ĉ���
-->
<def tag="BOX" contentsmode="arg" attributesname="attr">
  <return>
    <box caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <CIRCLE>�F�~
  �����F�iPDFJ��circle���\�b�h�̈������Q�Ɓj
  ���e�F�����Ƃ��ĉ���
-->
<def tag="CIRCLE" contentsmode="arg" attributesname="attr">
  <return>
    <circle caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <ELLIPSE>�F�ȉ~
  �����F�iPDFJ��ellipse���\�b�h�̈������Q�Ɓj
  ���e�F�����Ƃ��ĉ���
-->
<def tag="ELLIPSE" contentsmode="arg" attributesname="attr">
  <return>
    <ellipse caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <POLYGON>�F���p�`
  �����F�iPDFJ��polygon���\�b�h�̈������Q�Ɓj
        coords�����ɂ̓J���}��؂�ō��W����w��
  ���e�F�����Ƃ��ĉ���
-->
<def tag="POLYGON" contentsmode="arg" attributesname="attr">
  <eval>
    $Args{attr}{coords} = [split /\s*,\s*/, $Args{attr}{coords}];
  </eval>
  <return>
    <polygon caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <SHAPEOBJ>�F�}�`���̕\���\�I�u�W�F�N�g
  �����Fobj=�\���\�I�u�W�F�N�g
        showargs="X,Y,�z�u" X,Y�͈ʒu�i�}�`���ł̍��W�Łj
        �z�u�͎���l,c,r��t,m,b�̑g�ݍ��킹
        X�� l:���[�Ac:�����Ar:�E�[ �����킹��
        Y�� t:��[�Am:�����Ab:���[ �����킹��
  ���e�F�����Ƃ��ĉ���
-->
<def tag="SHAPEOBJ" contentsmode="arg" attributesname="attr">
  <eval>
    $Args{attr}{showargs} = [split /\s*,\s*/, $Args{attr}{showargs}];
  </eval>
  <return>
    <obj caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <BOUNDARY>�F�}�`�̋��E
  �����Fx=���ʒu
        y=�c�ʒu
        �w�肵�����ʒu�Əc�ʒu������܂ł̋��E���O�ɂ���΋��E���L����
        �i���E�����߂邱�Ƃ͂ł��Ȃ��j
  ���e�F�����Ƃ��ĉ���
-->
<def tag="BOUNDARY" contentsmode="arg" attributesname="attr">
  <return>
    <setboundary caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <ARC>�F�~��
  �����F�iPDFJ��arc���\�b�h�̈������Q�Ɓj
  ���e�F�����Ƃ��ĉ���
-->
<def tag="ARC" contentsmode="arg" attributesname="attr">
  <return>
    <arc caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <ARROW>�F���
  �����F<LINE>�̑����ɉ����āA
        headsize=�V�̒����i�ȗ������8�j
        headangle=�V�̐�[�p�x�̔����i���W�A���j�i�ȗ������0.3�j
        �I�[���V���t��
  ���e�F�����Ƃ��ĉ���
-->
<def tag="ARROW" contentsmode="arg" attributesname="attr"
headsize="8" headangle="0.3">
  <return>
    <arrow caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <BRACE>�F�g����
  �����Fx=���ʒu
        y=�c�ʒu
        w=�� 
        h=����
        style=�}�`�X�^�C���i�I�v�V�����j
        x,y,w,h�Ō��܂��`�̒��ɕ`�����B
        w�𕉂ɂ���ƕ����ʂɂȂ�B
  ���e�F�����Ƃ��ĉ���
-->
<def tag="BRACE" contentsmode="arg" attributesname="attr">
  <return>
    <brace caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <BRACKET>�F�p����
  �����Fx=���ʒu
        y=�c�ʒu
        w=�� 
        h=����
        style=�}�`�X�^�C���i�I�v�V�����j
        x,y,w,h�Ō��܂��`�̒��ɕ`�����B
        w�𕉂ɂ���ƕ����ʂɂȂ�B
  ���e�F�����Ƃ��ĉ���
-->
<def tag="BRACKET" contentsmode="arg" attributesname="attr">
  <return>
    <bracket caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <PAREN>�F�ۊ���
  �����Fx=���ʒu
        y=�c�ʒu
        w=�� 
        h=����
        style=�}�`�X�^�C���i�I�v�V�����j
        x,y,w,h�Ō��܂��`�̒��ɕ`�����B
        w�𕉂ɂ���ƕ����ʂɂȂ�B
  ���e�F�����Ƃ��ĉ���
-->
<def tag="PAREN" contentsmode="arg" attributesname="attr">
  <return>
    <paren caller="$Args{shape}" attributes="$Args{attr}"/>
  </return>
</def>

<!--
  <PARENBLOCK>�F���ʕt���u���b�N
  �������I�Ȃ��̂Ȃ̂Ńh�L�������g������
-->
<def tag="PARENBLOCK" direction="V" type="paren" pwidth="5" padding="3">
  <eval>
    die "begin or end attribute required for BRACEBLOCK" 
      unless $Args{begin} || $Args{end};
  </eval>
  <Block setvar="$_iblock" direction="$Args{direction}">
    <style><BStyle/></style>
    <objects><do contents="$Args{contents}"/></objects>
  </Block>
  <eval>
    $_size = $_iblock->size($Args{direction});
    $_odir = $Args{direction} eq 'V' ? 'H' : 'V';
    $_objects = [];
  </eval>
  <do if="$Args{begin}">
    <SHAPE setvar="$_shape">
      <do if="$Args{type} eq 'brace'">
        <BRACE x="0" y="0" w="$Args{pwidth}" h="$_size"/>
      </do>
      <do if="$Args{type} eq 'bracket'">
        <BRACKET x="0" y="0" w="$Args{pwidth}" h="$_size"/>
      </do>
      <do if="$Args{type} eq 'paren'">
        <PAREN x="0" y="0" w="$Args{pwidth}" h="$_size"/>
      </do>
    </SHAPE>
    <SKIP setvar="$_skip" skip="$Args{padding}"/>
    <eval>
      push @$_objects, $_shape, $_skip;
    </eval>
  </do>
  <eval>
    push @$_objects, $_iblock;
  </eval>
  <do if="$Args{end}">
    <eval>
      $_pwidth = -$Args{pwidth};
    </eval>
    <SHAPE setvar="$_shape">
      <do if="$Args{type} eq 'brace'">
        <BRACE x="0" y="0" w="$_pwidth" h="$_size"/>
      </do>
      <do if="$Args{type} eq 'bracket'">
        <BRACKET x="0" y="0" w="$_pwidth" h="$_size"/>
      </do>
      <do if="$Args{type} eq 'paren'">
        <PAREN x="0" y="0" w="$_pwidth" h="$_size"/>
      </do>
    </SHAPE>
    <SKIP setvar="$_skip" skip="$Args{padding}"/>
    <eval>
      push @$_objects, $_skip, $_shape;
    </eval>
  </do>
  <return>
    <Block direction="$_odir" objects="$_objects">
      <style><BStyle/></style>
    </Block>
  </return>
</def>

</do>