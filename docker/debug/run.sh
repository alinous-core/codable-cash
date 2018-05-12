#!/bin/bash

pushd ../..

projectSrc=$(pwd)
echo $projectSrc

popd

# t transfer host input to container
# i open stdout
# d background
# --name test-dev
docker container run --rm --privileged\
	-v $projectSrc:/var/codablecash \
	 ubuntu16 \
	/var/make.sh
