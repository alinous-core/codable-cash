#!/bin/bash

cd /var/codablecash/
rm -rf ./target/

./sh/cmakeDebug.sh
./sh/maketest.sh
./sh/makecheck.sh

useradd $1
chown -R $1:$1 ./target

