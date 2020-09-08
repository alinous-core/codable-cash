/*
 * AlterTableStatement.cpp
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#include "sql_ddl/AlterTableStatement.h"

namespace alinous {

AlterTableStatement::AlterTableStatement() : AbstractSQLStatement(CodeElement::DDL_ALTER_TABLE) {

}

AlterTableStatement::~AlterTableStatement() {

}

void AlterTableStatement::preAnalyze(AnalyzeContext* actx) {
}

void AlterTableStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void AlterTableStatement::analyze(AnalyzeContext* actx) {
}

int AlterTableStatement::binarySize() const {
}

void AlterTableStatement::toBinary(ByteBuffer* out) {
}

void AlterTableStatement::fromBinary(ByteBuffer* in) {
}

void AlterTableStatement::interpret(VirtualMachine* vm) {
}

} /* namespace alinous */
