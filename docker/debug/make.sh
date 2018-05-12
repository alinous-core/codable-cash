#!/bin/bash

cd /var/codablecash/
rm -rf ./target/

./sh/cmakeDebug.sh
./sh/maketest.sh
./sh/makecheck.sh


echo "useradd $1 -u $2 -g $3"
echo "chown $1:$1 -R ./target"

groupadd -g $3 $1
useradd $1 -u $2 -g $3
chown $1:$1 -R ./target

