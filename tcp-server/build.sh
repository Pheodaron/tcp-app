#!/bin/bash

rm -rf ./build
mkdir build
cd ./build
cmake ../
make
find . ! -name "tcp-server" -delete
