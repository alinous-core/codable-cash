#!/bin/sh

echo 'Build latest CppUTest'
set -e

mkdir cpputest
cd cpputest

git clone https://github.com/cpputest/cpputest.git

cd cpputest
git checkout v3.8
cmake CMakeLists.txt
make install
cd ../..


