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
	this->name = nullptr;
	this->list = new ArrayList<DdlColumnDescriptor>();
	this->primaryKeys = new ArrayList<UnicodeString>();
}

CreateTableStatement::~CreateTableStatement() {
	delete this->name;

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
	checkNotNull(this->name);

	int total = sizeof(uint16_t);

	total += stringSize(this->name);

	total += sizeof(int32_t);
	int maxLoop = this->list->size();
	for(int i = 0; i != maxLoop; ++i){
		DdlColumnDescriptor* col = this->list->get(i);
		total += col->binarySize();
	}

	return total;
}

void CreateTableStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::DDL_CREATE_TABLE);

	putString(out, this->name);

	int maxLoop = this->list->size();
	out->putInt(maxLoop);
	for(int i = 0; i != maxLoop; ++i){
		DdlColumnDescriptor* col = this->list->get(i);
		col->toBinary(out);
	}
}

void CreateTableStatement::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);

		DdlColumnDescriptor* col = dynamic_cast<DdlColumnDescriptor*>(element);
		this->list->addElement(col);
	}
}

void CreateTableStatement::interpret(VirtualMachine* vm) {
	// FIXME SQL statement
}

void CreateTableStatement::addColumn(DdlColumnDescriptor* col) noexcept {
	this->list->addElement(col);
}

void CreateTableStatement::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void CreateTableStatement::addPrimaryKey(UnicodeString* key) noexcept {
	this->primaryKeys->addElement(key);
}

} /* namespace alinous */
