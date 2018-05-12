#!/bin/bash -eux

pushd docker/debug/
./run_jenkins.sh
popd

