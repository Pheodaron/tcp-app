#!/bin/bash

rm -rf ./build
mkdir build
cd ./build
cmake ../
make
find . ! -name "tcp-server" -delete

cd ..
mkdir ./tcp-server/
mkdir ./tcp-server/bin
cp ./build/tcp-server ./tcp-server/bin
mkdir ./tcp-server/DEBIAN/
cp ./debian-manifest/control ./tcp-server/DEBIAN/

dpkg-deb --root-owner-group --build tcp-server
rm -rf ./tcp-server
