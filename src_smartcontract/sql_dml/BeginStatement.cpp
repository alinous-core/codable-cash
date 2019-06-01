/*
 * BeginStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_dml/BeginStatement.h"

namespace alinous {

BeginStatement::BeginStatement() : AbstractSQLStatement(CodeElement::DML_STMT_BEGIN) {
}

BeginStatement::~BeginStatement() {
}

void BeginStatement::preAnalyze(AnalyzeContext* actx) {
}

void BeginStatement::analyze(AnalyzeContext* actx) {
}

int BeginStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void BeginStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DML_STMT_BEGIN);
}

void BeginStatement::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
