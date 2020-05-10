/*
 * CreateTableStatement.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_ddl/CreateTableStatement.h"

#include "sql_ddl/DdlColumnDescriptor.h"

#include "base/UnicodeString.h"

namespace alinous {

CreateTableStatement::CreateTableStatement() : AbstractSQLStatement(CodeElement::DDL_CREATE_TABLE) {
	this->list = new ArrayList<DdlColumnDescriptor>();
	this->primaryKeys = new ArrayList<UnicodeString>();
}

CreateTableStatement::~CreateTableStatement() {
	this->list->deleteElements();
	delete this->list;

	this->primaryKeys->deleteElements();
	delete this->primaryKeys;
}

void CreateTableStatement::preAnalyze(AnalyzeContext* actx) {
}

void CreateTableStatement::analyzeTypeRef(AnalyzeContext* actx) {
}


void CreateTableStatement::analyze(AnalyzeContext* actx) {
}

int CreateTableStatement::binarySize() const {
	int total = sizeof(uint16_t);


	return total;
}

void CreateTableStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::DDL_CREATE_TABLE);
}

void CreateTableStatement::fromBinary(ByteBuffer* in) {
}

void CreateTableStatement::interpret(VirtualMachine* vm) {
	// FIXME SQL statement
}

void CreateTableStatement::addColumn(DdlColumnDescriptor* col) noexcept {
	this->list->addElement(col);
}

void CreateTableStatement::addPrimaryKey(UnicodeString* key) noexcept {
	this->primaryKeys->addElement(key);
}

} /* namespace alinous */
