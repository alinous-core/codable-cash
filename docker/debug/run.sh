#!/bin/bash

execuser=$(whoami)
if [ -n "$1" ]; then
  execuser=$1
fi

echo "user : $execuser"

pushd ../..

projectSrc=$(pwd)
echo $projectSrc

popd

# t transfer host input to container
# i open stdout
# d background
# --name test-dev
docker container run --rm \
	-v /var/run/docker.sock:/var/run/docker.sock \
	-v $projectSrc:/var/codablecash \
	 ubuntu16 \
	/var/make.sh $execuser
