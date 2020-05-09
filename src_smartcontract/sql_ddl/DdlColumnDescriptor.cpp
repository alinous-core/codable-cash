/*
 * DdlColumnDescriptor.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "sql_ddl/DdlColumnDescriptor.h"

#include "base/UnicodeString.h"

#include "sql_ddl/ColumnTypeDescriptor.h"

#include "sql/AbstractSQLExpression.h"

namespace alinous {

DdlColumnDescriptor::DdlColumnDescriptor() : AbstractSQLPart(CodeElement::DDL_COLMUN_DESC)  {
	this->name = nullptr;
	this->typeDesc = nullptr;
	this->notNull = false;
	this->unique = false;
	this->defaultValue = nullptr;
}

DdlColumnDescriptor::~DdlColumnDescriptor() {
	delete this->name;
	delete this->typeDesc;
	delete this->defaultValue;
}

int DdlColumnDescriptor::binarySize() const {
}

void DdlColumnDescriptor::toBinary(ByteBuffer* out) {
}

void DdlColumnDescriptor::fromBinary(ByteBuffer* in) {
}

void DdlColumnDescriptor::setName(UnicodeString* name) noexcept {
	this->name = name;
}

void DdlColumnDescriptor::setColumnType(ColumnTypeDescriptor* typeDesc) noexcept {
	this->typeDesc = typeDesc;
}

void DdlColumnDescriptor::setUnique(bool unique) noexcept {
	this->unique = unique;
}

void DdlColumnDescriptor::setNotNull(bool notNull) noexcept {
	this->notNull = notNull;
}

void DdlColumnDescriptor::setDefaultValue(AbstractSQLExpression* defaultValue) noexcept {
	this->defaultValue = defaultValue;
}

} /* namespace alinous */
