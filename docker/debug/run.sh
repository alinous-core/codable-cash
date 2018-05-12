#!/bin/bash

pushd ../..

projectSrc=$(pwd)
echo $projectSrc

popd

# t transfer host input to container
# i open stdout
# d background
docker container run --rm --name test-dev \
	-v $projectSrc:/var/codablecash \
	-it ubuntu16 \
	/var/make.sh
