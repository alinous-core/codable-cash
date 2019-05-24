/*
 * RollbackStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/RollbackStatement.h"

namespace alinous {

RollbackStatement::RollbackStatement() : AbstractSQLStatement(CodeElement::DML_STMT_ROLLBACK) {
}

RollbackStatement::~RollbackStatement() {
}

void RollbackStatement::preAnalyze(AnalyzeContext* actx) {
}

void RollbackStatement::analyze(AnalyzeContext* actx) {
}

int RollbackStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void RollbackStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DML_STMT_ROLLBACK);
}

void RollbackStatement::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
