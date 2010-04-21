PDFJ - 日本語PDF生成モジュール
バージョン 0.72

2003/11/7
中島 靖 <nakajima@netstock.co.jp>

【ファイル構成】

PDFJ.pm     … PDFJの本体のモジュールファイル
PDFJ/*.pm   … PDFJ.pmから呼ばれて使われる下請けモジュール
PDFJ.jp.pdf … PDFJ説明書（PDFJ.jp.podをpod2pdf.plで処理したもの）
PDFJ.jp.pod … PDFJ説明書のpod形式でのソース
XPDFJ.pm    … PDFJのXMLフロントエンドであるXPDFJのモジュールファイル
XPDFJ.jp.pdf… XPDFJ説明書（XPDFJ.jp.podをpod2pdf.plで処理したもの）
XPDFJ.jp.pod… XPDFJ説明書のpod形式でのソース
demo.pl     … サンプルスクリプト（demo.pdfを生成）
demo.pdf    … demo.plによって生成されたPDFファイル
frame.jpg   … demo.plで使われている画像ファイル
text2pdf.pl … サンプルスクリプト（テキストファイルをPDFに）
pod2pdf.pl  … サンプルスクリプト（podをPDFに）
nouhinsho.pl… サンプルスクリプト（納品書作成）
nouhinsho.dat…nouhinsho.plのサンプルデータ
xpdfj.pl    … XPDFJを使ってXMLからPDFを生成するスクリプト
demo.xp     … demo.plをXPDFJ用のXMLに書き直したもの（マクロ使用無し）
of2002.xp   … XPDFJ用のサンプルXML（マクロ機能を使用）
of2002.inc  … of2002.xpから読み込まれる
of2002.pdf  … of2002.xpから生成されたPDFファイル
stddefs.inc … XPDFJ用のマクロファイル
stdfontsH.inc…XPDFJ用のフォント定義ファイル（横書用）
stdfontsV.inc…XPDFJ用のフォント定義ファイル（縦書用）
ttfinfo.pl  … TrueTypeフォントファイル(.ttf)の内容を調べるスクリプト
ttcinfo.pl  … TrueTypeCollectionファイル(.ttc)の内容を調べるスクリプト
readme.txt  … このファイル
Makefile.PL … インストール時に使われるスクリプト
CHANGES     … 変更点を記載している
TODO        … 今後の予定を記載している

【インストール】

管理者であれば次の標準的な手順でインストールできる。

  perl Makefile.PL
  make
  make install

最後のmake installは管理者権限で実行する。Windowsではmakeでなくnmakeを使用する。

管理者でない場合でも、PDFJを構成する次のモジュールファイル群をPerlから利用できる（すなわち@INCにセットされた）ディレクトリにおけば利用できる。

  PDFJ.pm
  PDFJ/Object.pm
  PDFJ/Unicode.pm
  PDFJ/E2U.pm
  PDFJ/S2U.pm
  PDFJ/U2C.pm
  PDFJ/TTF.pm

PDFJは、欧文のハイフネーションをおこなうために、TeX::Hyphenモジュールを使用している。欧文を含むテキストを扱う場合は必要となるので、CPANからダウンロードしてインストールしておく。管理者でない場合は、次のモジュールをPerlから利用できるディレクトリにおけばよい。

  TeX/Hyphen.pm
  TeX/Hyphen/czech.pm
  TeX/Hyphen/german.pm

PDFJは、フォントや画像などのデータを埋め込む際に、デフォルトではCompress::Zlibモジュールを使用する。Compress::Zlibがない環境や、Compress::Zlibを使いたくない場合のために、Compress::Zlibを使わずにデータの埋め込みをおこなうオプションも用意されている。

【説明書について】

まず最初に、of2002.pdfやdemo.pdfをご覧いただくと、PDFJがどんなソフトで、どんなことができるか概要を掴んでいただけると思います。これらのpdfファイル自体がPDFJおよびXPDFJによって作られたものです。

PDFJ.jp.pdfがPDFJの、XPDFJ.jp.pdfがXPDFJの、それぞれ説明書ですのでご覧下さい。

stddefs.incについてはそれ自体に簡単な説明を記載しています。

【サンプルスクリプトtext2pdf.plについて】

テキストファイルをpdfファイルに変換します。

  perl text2pdf.pl 入力ファイル 出力ファイル

と実行します。

あくまでサンプルであり、次の制約があります。

・タブの処理は行頭のタブに限定されている。

また、同梱のtext2pdf.plはShiftJIS用であり、EUCテキストに対して使用するには、「use PDFJ 'SJIS';」を「use PDFJ 'EUC';」に変更する必要があります。

【サンプルスクリプトpod2pdf.plについて】

Perlの標準的な説明書記述形式であるpodをpdfに変換します。

  perl pod2pdf.pl 入力ファイル 出力ファイル

と実行します。

実行するには、Pod::Parserモジュールが必要です。（Perl5.6以降には標準添付）

あくまでサンプルであり、次の制約があります。

・=begin、=end、=forは無視される
・タブのスペースへの置き換えはおこなわれない
・B<…>などの内部シーケンスは次のものだけが処理され、それ以外は元の文字列そのものとなる
  I<> B<> C<> F<> E<lt> E<gt> E<sol> E<verbar> L<"…"> L<…|"…"> X<>
  ※L<>のリンク先は、=head1と=head2の見出し、X<>で指定した場所、URL（https?、ftp、mailto）へのリンクのみ可能
  ※X<>はリンク先名の指定となる（それ自体は表示されない）

また、同梱のpod2pdf.plはShiftJIS用であり、EUCテキストに対して使用するには、「use PDFJ 'SJIS';」を「use PDFJ 'EUC';」に変更するとともに、pod2pdf.pl自体をEUCで保存し直す必要があります。

なお、シフトJISでは、内部シーケンスでない「<」をそのまま書くと、その前に来る文字（例えば「、」「。」など）によっては内部シーケンスと誤って解釈して文字化けしたような出力になる場合があるので注意してください。

【サンプルスクリプトnouhinsho.plについて】

帳票作成のサンプルです。

  perl nouhinsho.pl nouhinsho.dat nouhinsho.pdf

で、データファイルnouhinsho.datに従って、nouhinsho.pdfが作成されます。

【XPDFJ関係】

XPDFJを使用するには、XML::Parserモジュールが必要です。

XPDFJの書式によるXMLファイルをPDFに変換するには、

  perl xpdfj.pl 入力ファイル名 出力ファイル名

と実行します。

サンプルのXMLファイルとして、demo.xp、of2002.xpが付属しています。demo.xpは、demo.plの内容をマクロ機能を使わずにストレートにXML化したものです。of2002.xpは、stddefs.incで定義されたマクロを使用した例となっています。

【TrueTypeフォントツール】

TrueTypeフォントの内容を調べるためのツールとして、.ttf用のttfinfo.plと.ttc用のttcinfo.plが付属している。

.ttcファイルに含まれるフォント名（Postscriptフォント名）を見たいときは、

  perl ttcinfo.pl foo.ttc -n

のようにする。

フォントの詳しい内容を見たい場合は、

  perl ttfinfo.pl bar.ttf

  perl ttcinfo.pl foo.ttc

のようにすると、bar.ttf.info や foo.ttc.info というファイルが作られる。

【使用条件】

本ソフトウェアは誰でも自由に使用、配布、改良およびそれらの組み合わせをおこなうことができます。ただし、改良したものを配布する場合は原著作者の表示を保持してください。

本ソフトウェアは無保証であり、使用した結果に対しても責任を負えません。

本ソフトウェアはαバージョンの段階にあり、予告なく仕様が変更されることが大いにあり得ます。

【気づいた点は…】

本ソフトウェアについてのバグレポート、ご意見などは、下記のメーリングリストにご参加の上、投稿ください。ただし、バグの修正やご質問への回答についてお約束するものではなく、みんなでよりよいソフトウェアを作っていこうという趣旨で運営しております。よろしくお願いします。

PDFJメーリングリスト：
参加申込用アドレス：nakajima.yasushi-pdfj-subscribe@jonex.ne.jp
投稿用アドレス：nakajima.yasushi-pdfj@jonex.ne.jp

謝辞：本ソフトウェアの作成にあたっては、Kansai.pmのみなさんから多くの提案や励ましや催促(^^)をいただきました。記して感謝いたします。
