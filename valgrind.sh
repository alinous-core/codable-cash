#!/bin/bash -eux


pushd target
make valgrind
popd
