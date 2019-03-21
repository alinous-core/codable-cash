/*
 * CreateTableStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_ddl/CreateTableStatement.h"

namespace alinous {

CreateTableStatement::CreateTableStatement() : AbstractSQLStatement(CodeElement::DDL_CREATE_TABLE) {

}

CreateTableStatement::~CreateTableStatement() {

}


int alinous::CreateTableStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void alinous::CreateTableStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DDL_CREATE_TABLE);
}

void alinous::CreateTableStatement::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
