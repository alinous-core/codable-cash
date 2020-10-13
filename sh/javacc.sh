#!/bin/bash -eux

if test -e src_smartcontract/engine/jj/alinous.jj ; then
  rm src_smartcontract/engine/jj/alinous.jj
fi

cat src_smartcontract/engine/jj/header.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/lex.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/base.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/types.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/statement.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/statement_ctrl.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/expression.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/sql_ddl.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/sql_dml.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/sql_expression.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/sql_join.jj >> src_smartcontract/engine/jj/alinous.jj
cat src_smartcontract/engine/jj/json.jj >> src_smartcontract/engine/jj/alinous.jj

java -classpath ./tools/javacc-7.0.4.jar javacc -STATIC=false ./src_smartcontract/engine/jj/alinous.jj
#java -classpath ./tools/javacc-7.0.4.jar javacc -STATIC=false -LOOKAHEAD:3 ./src_smartcontract/engine/jj/alinous.jj

