#!/bin/bash -eux


if test -e target ; then
  rm -rf ./target/
fi

mkdir target

pushd target

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++-7 -DCMAKE_C_COMPILER=gcc-7 ..

make all
make test ARGS='-V'
make report

popd
