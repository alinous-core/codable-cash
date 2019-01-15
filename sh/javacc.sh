#!/bin/bash -eux


java -classpath ./tools/javacc-7.0.4.jar javacc -STATIC=false -LOOKAHEAD:3 ./src_smartcontract/sc/alinous.jj

