#!/bin/bash -eux


pushd target
make all -j4
make test
make report
popd
