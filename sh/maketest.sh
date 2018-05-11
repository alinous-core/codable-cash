#!/bin/bash -eux


pushd target
make all -j4
make test ARGS='-V'
make report
popd
