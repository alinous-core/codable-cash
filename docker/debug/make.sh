#!/bin/bash

cd /var/codablecash/
rm -rf ./target/

./sh/cmakeDebug.sh
./sh/maketest.sh

useradd $1
chown -R $1:$1 ./target



