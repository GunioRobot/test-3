PDFJ - ���{��PDF�������W���[��
�o�[�W���� 0.72

2003/11/7
���� �� <nakajima@netstock.co.jp>

�y�t�@�C���\���z

PDFJ.pm     �c PDFJ�̖{�̂̃��W���[���t�@�C��
PDFJ/*.pm   �c PDFJ.pm����Ă΂�Ďg���鉺�������W���[��
PDFJ.jp.pdf �c PDFJ�������iPDFJ.jp.pod��pod2pdf.pl�ŏ����������́j
PDFJ.jp.pod �c PDFJ��������pod�`���ł̃\�[�X
XPDFJ.pm    �c PDFJ��XML�t�����g�G���h�ł���XPDFJ�̃��W���[���t�@�C��
XPDFJ.jp.pdf�c XPDFJ�������iXPDFJ.jp.pod��pod2pdf.pl�ŏ����������́j
XPDFJ.jp.pod�c XPDFJ��������pod�`���ł̃\�[�X
demo.pl     �c �T���v���X�N���v�g�idemo.pdf�𐶐��j
demo.pdf    �c demo.pl�ɂ���Đ������ꂽPDF�t�@�C��
frame.jpg   �c demo.pl�Ŏg���Ă���摜�t�@�C��
text2pdf.pl �c �T���v���X�N���v�g�i�e�L�X�g�t�@�C����PDF�Ɂj
pod2pdf.pl  �c �T���v���X�N���v�g�ipod��PDF�Ɂj
nouhinsho.pl�c �T���v���X�N���v�g�i�[�i���쐬�j
nouhinsho.dat�cnouhinsho.pl�̃T���v���f�[�^
xpdfj.pl    �c XPDFJ���g����XML����PDF�𐶐�����X�N���v�g
demo.xp     �c demo.pl��XPDFJ�p��XML�ɏ������������́i�}�N���g�p�����j
of2002.xp   �c XPDFJ�p�̃T���v��XML�i�}�N���@�\���g�p�j
of2002.inc  �c of2002.xp����ǂݍ��܂��
of2002.pdf  �c of2002.xp���琶�����ꂽPDF�t�@�C��
stddefs.inc �c XPDFJ�p�̃}�N���t�@�C��
stdfontsH.inc�cXPDFJ�p�̃t�H���g��`�t�@�C���i�����p�j
stdfontsV.inc�cXPDFJ�p�̃t�H���g��`�t�@�C���i�c���p�j
ttfinfo.pl  �c TrueType�t�H���g�t�@�C��(.ttf)�̓��e�𒲂ׂ�X�N���v�g
ttcinfo.pl  �c TrueTypeCollection�t�@�C��(.ttc)�̓��e�𒲂ׂ�X�N���v�g
readme.txt  �c ���̃t�@�C��
Makefile.PL �c �C���X�g�[�����Ɏg����X�N���v�g
CHANGES     �c �ύX�_���L�ڂ��Ă���
TODO        �c ����̗\����L�ڂ��Ă���

�y�C���X�g�[���z

�Ǘ��҂ł���Ύ��̕W���I�Ȏ菇�ŃC���X�g�[���ł���B

  perl Makefile.PL
  make
  make install

�Ō��make install�͊Ǘ��Ҍ����Ŏ��s����BWindows�ł�make�łȂ�nmake���g�p����B

�Ǘ��҂łȂ��ꍇ�ł��APDFJ���\�����鎟�̃��W���[���t�@�C���Q��Perl���痘�p�ł���i���Ȃ킿@INC�ɃZ�b�g���ꂽ�j�f�B���N�g���ɂ����Η��p�ł���B

  PDFJ.pm
  PDFJ/Object.pm
  PDFJ/Unicode.pm
  PDFJ/E2U.pm
  PDFJ/S2U.pm
  PDFJ/U2C.pm
  PDFJ/TTF.pm

PDFJ�́A�����̃n�C�t�l�[�V�����������Ȃ����߂ɁATeX::Hyphen���W���[�����g�p���Ă���B�������܂ރe�L�X�g�������ꍇ�͕K�v�ƂȂ�̂ŁACPAN����_�E�����[�h���ăC���X�g�[�����Ă����B�Ǘ��҂łȂ��ꍇ�́A���̃��W���[����Perl���痘�p�ł���f�B���N�g���ɂ����΂悢�B

  TeX/Hyphen.pm
  TeX/Hyphen/czech.pm
  TeX/Hyphen/german.pm

PDFJ�́A�t�H���g��摜�Ȃǂ̃f�[�^�𖄂ߍ��ލۂɁA�f�t�H���g�ł�Compress::Zlib���W���[�����g�p����BCompress::Zlib���Ȃ�����ACompress::Zlib���g�������Ȃ��ꍇ�̂��߂ɁACompress::Zlib���g�킸�Ƀf�[�^�̖��ߍ��݂������Ȃ��I�v�V�������p�ӂ���Ă���B

�y�������ɂ��āz

�܂��ŏ��ɁAof2002.pdf��demo.pdf���������������ƁAPDFJ���ǂ�ȃ\�t�g�ŁA�ǂ�Ȃ��Ƃ��ł��邩�T�v��͂�ł���������Ǝv���܂��B������pdf�t�@�C�����̂�PDFJ�����XPDFJ�ɂ���č��ꂽ���̂ł��B

PDFJ.jp.pdf��PDFJ�́AXPDFJ.jp.pdf��XPDFJ�́A���ꂼ��������ł��̂ł����������B

stddefs.inc�ɂ��Ă͂��ꎩ�̂ɊȒP�Ȑ������L�ڂ��Ă��܂��B

�y�T���v���X�N���v�gtext2pdf.pl�ɂ��āz

�e�L�X�g�t�@�C����pdf�t�@�C���ɕϊ����܂��B

  perl text2pdf.pl ���̓t�@�C�� �o�̓t�@�C��

�Ǝ��s���܂��B

�����܂ŃT���v���ł���A���̐��񂪂���܂��B

�E�^�u�̏����͍s���̃^�u�Ɍ��肳��Ă���B

�܂��A������text2pdf.pl��ShiftJIS�p�ł���AEUC�e�L�X�g�ɑ΂��Ďg�p����ɂ́A�uuse PDFJ 'SJIS';�v���uuse PDFJ 'EUC';�v�ɕύX����K�v������܂��B

�y�T���v���X�N���v�gpod2pdf.pl�ɂ��āz

Perl�̕W���I�Ȑ������L�q�`���ł���pod��pdf�ɕϊ����܂��B

  perl pod2pdf.pl ���̓t�@�C�� �o�̓t�@�C��

�Ǝ��s���܂��B

���s����ɂ́APod::Parser���W���[�����K�v�ł��B�iPerl5.6�ȍ~�ɂ͕W���Y�t�j

�����܂ŃT���v���ł���A���̐��񂪂���܂��B

�E=begin�A=end�A=for�͖��������
�E�^�u�̃X�y�[�X�ւ̒u�������͂����Ȃ��Ȃ�
�EB<�c>�Ȃǂ̓����V�[�P���X�͎��̂��̂�������������A����ȊO�͌��̕����񂻂̂��̂ƂȂ�
  I<> B<> C<> F<> E<lt> E<gt> E<sol> E<verbar> L<"�c"> L<�c|"�c"> X<>
  ��L<>�̃����N��́A=head1��=head2�̌��o���AX<>�Ŏw�肵���ꏊ�AURL�ihttps?�Aftp�Amailto�j�ւ̃����N�̂݉\
  ��X<>�̓����N�於�̎w��ƂȂ�i���ꎩ�͕̂\������Ȃ��j

�܂��A������pod2pdf.pl��ShiftJIS�p�ł���AEUC�e�L�X�g�ɑ΂��Ďg�p����ɂ́A�uuse PDFJ 'SJIS';�v���uuse PDFJ 'EUC';�v�ɕύX����ƂƂ��ɁApod2pdf.pl���̂�EUC�ŕۑ��������K�v������܂��B

�Ȃ��A�V�t�gJIS�ł́A�����V�[�P���X�łȂ��u<�v�����̂܂܏����ƁA���̑O�ɗ��镶���i�Ⴆ�΁u�A�v�u�B�v�Ȃǁj�ɂ���Ă͓����V�[�P���X�ƌ���ĉ��߂��ĕ������������悤�ȏo�͂ɂȂ�ꍇ������̂Œ��ӂ��Ă��������B

�y�T���v���X�N���v�gnouhinsho.pl�ɂ��āz

���[�쐬�̃T���v���ł��B

  perl nouhinsho.pl nouhinsho.dat nouhinsho.pdf

�ŁA�f�[�^�t�@�C��nouhinsho.dat�ɏ]���āAnouhinsho.pdf���쐬����܂��B

�yXPDFJ�֌W�z

XPDFJ���g�p����ɂ́AXML::Parser���W���[�����K�v�ł��B

XPDFJ�̏����ɂ��XML�t�@�C����PDF�ɕϊ�����ɂ́A

  perl xpdfj.pl ���̓t�@�C���� �o�̓t�@�C����

�Ǝ��s���܂��B

�T���v����XML�t�@�C���Ƃ��āAdemo.xp�Aof2002.xp���t�����Ă��܂��Bdemo.xp�́Ademo.pl�̓��e���}�N���@�\���g�킸�ɃX�g���[�g��XML���������̂ł��Bof2002.xp�́Astddefs.inc�Œ�`���ꂽ�}�N�����g�p������ƂȂ��Ă��܂��B

�yTrueType�t�H���g�c�[���z

TrueType�t�H���g�̓��e�𒲂ׂ邽�߂̃c�[���Ƃ��āA.ttf�p��ttfinfo.pl��.ttc�p��ttcinfo.pl���t�����Ă���B

.ttc�t�@�C���Ɋ܂܂��t�H���g���iPostscript�t�H���g���j���������Ƃ��́A

  perl ttcinfo.pl foo.ttc -n

�̂悤�ɂ���B

�t�H���g�̏ڂ������e���������ꍇ�́A

  perl ttfinfo.pl bar.ttf

  perl ttcinfo.pl foo.ttc

�̂悤�ɂ���ƁAbar.ttf.info �� foo.ttc.info �Ƃ����t�@�C���������B

�y�g�p�����z

�{�\�t�g�E�F�A�͒N�ł����R�Ɏg�p�A�z�z�A���ǂ���т����̑g�ݍ��킹�������Ȃ����Ƃ��ł��܂��B�������A���ǂ������̂�z�z����ꍇ�͌�����҂̕\����ێ����Ă��������B

�{�\�t�g�E�F�A�͖��ۏ؂ł���A�g�p�������ʂɑ΂��Ă��ӔC�𕉂��܂���B

�{�\�t�g�E�F�A�̓��o�[�W�����̒i�K�ɂ���A�\���Ȃ��d�l���ύX����邱�Ƃ��傢�ɂ��蓾�܂��B

�y�C�Â����_�́c�z

�{�\�t�g�E�F�A�ɂ��Ẵo�O���|�[�g�A���ӌ��Ȃǂ́A���L�̃��[�����O���X�g�ɂ��Q���̏�A���e���������B�������A�o�O�̏C���₲����ւ̉񓚂ɂ��Ă��񑩂�����̂ł͂Ȃ��A�݂�Ȃł��悢�\�t�g�E�F�A������Ă������Ƃ�����|�ŉ^�c���Ă���܂��B��낵�����肢���܂��B

PDFJ���[�����O���X�g�F
�Q���\���p�A�h���X�Fnakajima.yasushi-pdfj-subscribe@jonex.ne.jp
���e�p�A�h���X�Fnakajima.yasushi-pdfj@jonex.ne.jp

�ӎ��F�{�\�t�g�E�F�A�̍쐬�ɂ������ẮAKansai.pm�݂̂Ȃ��񂩂瑽���̒�Ă��܂���Ñ�(^^)�����������܂����B�L���Ċ��ӂ������܂��B
