#!/bin/bash -eux


pushd target

mkdir -p cppcheck
make all -j4
make cppcheck
popd
