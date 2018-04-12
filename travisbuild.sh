#!/bin/bash -eux


if test -e target ; then
  rm -rf ./target/
fi

mkdir target

pushd target
cmake -DCMAKE_BUILD_TYPE=Debug ..

make all
make test
make report

popd