#!/bin/bash

change_owner () {
	echo "useradd $1 -u $2 -g $3"
	echo "chown $1:$1 -R ./target"
	
	groupadd -g $3 $1
	useradd $1 -u $2 -g $3
	chown $1:$1 -R ./target
}

cd /var/codablecash/
rm -rf ./target/

./sh/cmakeDebug.sh
./sh/maketest.sh
./sh/valgrind.sh
./sh/makecheck.sh

change_owner $1 $2 $3

