#!/bin/sh

echo 'Build latest CppUTest'
set -e

mkdir ext
cd ext

git clone https://github.com/cpputest/cpputest.git

cd cpputest
git checkout v3.8
cmake CMakeLists.txt
make install
cd ../..


