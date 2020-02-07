#!/bin/bash -eux


pushd target
make valgrindp
popd
