#!/bin/bash

cd /var/codablecash/
rm -rf ./target/

./sh/cmakeDebug.sh
./sh/maketest.sh
