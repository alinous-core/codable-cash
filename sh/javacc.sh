#!/bin/bash -eux

if test -e src_smartcontract/jj/alinous.jj ; then
  rm src_smartcontract/jj/alinous.jj
fi

cat src_smartcontract/jj/header.jj >> src_smartcontract/jj/alinous.jj
cat src_smartcontract/jj/lex.jj >> src_smartcontract/jj/alinous.jj
cat src_smartcontract/jj/base.jj >> src_smartcontract/jj/alinous.jj
cat src_smartcontract/jj/types.jj >> src_smartcontract/jj/alinous.jj

java -classpath ./tools/javacc-7.0.4.jar javacc -STATIC=false ./src_smartcontract/jj/alinous.jj
#java -classpath ./tools/javacc-7.0.4.jar javacc -STATIC=false -LOOKAHEAD:3 ./src_smartcontract/jj/alinous.jj

