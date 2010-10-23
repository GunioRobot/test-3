package Plagger::Plugin::Publish::DumpYAML;

use strict;
use base qw(Plagger::Plugin);

#
# Plagger Plugin作成のテスト
#

our $VERSION = '0.01';

use Data::Dumper;
use YAML qw(DumpFile);
use Encode;

use Class::Accessor;
use base qw(Class::Accessor);
__PACKAGE__->mk_accessors( qw(dumpdata));

# hookポイントの指定？
sub register {
  my($self,$context) = @_;

  $context->register_hook(
    $self,
    'publish.entry' =>  \&update,
    'plugin.init'   =>  \&initialize,
  );
}


# 初期化？
sub initialize {
  my ($self,$context,$args) = @_;
  print "----------------------------------------------\n";
  $self->dumpdata({});
#  $self->dumpdata->{feed} = {
#    'hoge' => 'fuga',
#  };
}


# コールバック処理？
sub update {
  my ($self,$context,$args) = @_;

  my $feed_title = encode('utf-8', $args->{entry}->{title});
  my $feed_link  = $args->{entry}->{link};

#  print Dumper $self->dumpdata;

  my $self->dumpdata->{feed}  = {
      'title' => $feed_title,
      'link'  => $feed_link,
  };

#  print Dumper $self->dumpdata;
#  YAML::DumpFile($self->{conf}->{filename},@yaml_data);

}

1;
