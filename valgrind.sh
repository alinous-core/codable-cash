#!/bin/bash -eux


pushd target


valgrind ./testall -v -gRAFTestGroup
popd
