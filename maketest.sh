#!/bin/bash -eux


pushd target
make all
make test
make report
popd
