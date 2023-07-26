#!/bin/bash

rm -rf ./build
mkdir build
cd ./build
cmake ../
make
find . ! -name "tcp-client" -delete

cd ..
mkdir ./tcp-client/
mkdir ./tcp-client/bin
cp ./build/tcp-client ./tcp-client/bin
mkdir ./tcp-client/DEBIAN/
cp ./debian-manifest/control ./tcp-client/DEBIAN/

dpkg-deb --root-owner-group --build tcp-client
rm -rf ./tcp-client
