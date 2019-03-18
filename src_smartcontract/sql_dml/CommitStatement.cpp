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

} /* namespace alinous */

int alinous::CommitStatement::binarySize() const {
}

void alinous::CommitStatement::toBinary(ByteBuffer* out) {
}

void alinous::CommitStatement::fromBinary(ByteBuffer* in) {
}
