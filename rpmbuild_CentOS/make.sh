#!/bin/bash

# http://stackoverflow.com/questions/880227/what-is-the-minimum-i-have-to-do-to-create-an-rpm-file

set -e
set -u

if [ -d udm-$VERSION ]; then true rm -rf udm-$VERSION; fi
pushd ..
VERSION=3.13
./configure LDFLAGS="-L$(pwd)/debian/zlib-1.2.3.3.dfsg/contrib/minizip/" CPPFLAGS="-I$(pwd)/debian/zlib-1.2.3.3.dfsg/contrib/"  CXXFLAGS="-I$(pwd)/debian/zlib-1.2.3.3.dfsg/contrib/" --with-pccts-dir=/usr/include/antlr/ --without-xalan --without-antlr --prefix=/usr
make DESTDIR=`pwd`/rpmbuild/udm-$VERSION install
popd

tar -zcvf udm-$VERSION.tar.gz udm-$VERSION
cp -f udm-$VERSION.tar.gz SOURCES/

rpmbuild -ba SPECS/udm.spec
