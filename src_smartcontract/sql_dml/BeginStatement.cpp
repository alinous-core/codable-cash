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

} /* namespace alinous */

int alinous::BeginStatement::binarySize() const {
}

void alinous::BeginStatement::toBinary(ByteBuffer* out) {
}

void alinous::BeginStatement::fromBinary(ByteBuffer* in) {
}
