#!/bin/bash -eux


pushd target
make all -j4
make cppcheck
popd
