/*
 * CommitStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/CommitStatement.h"

namespace alinous {

CommitStatement::CommitStatement() : AbstractSQLStatement(CodeElement::DML_STMT_COMMIT) {
}

CommitStatement::~CommitStatement() {
}

void CommitStatement::preAnalyze(AnalyzeContext* actx) {
}

void CommitStatement::analyze(AnalyzeContext* actx) {
}

int CommitStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void CommitStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DML_STMT_COMMIT);
}

void CommitStatement::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
