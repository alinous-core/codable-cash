/*
 * ColumnTypeDescriptor.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "sql_ddl/ColumnTypeDescriptor.h"

#include "sql/AbstractSQLExpression.h"

#include "base/UnicodeString.h"


namespace alinous {

ColumnTypeDescriptor::ColumnTypeDescriptor() : AbstractSQLPart(CodeElement::DDL_TYPE_DESC) {
	this->typeName = nullptr;
	this->length = nullptr;
}

ColumnTypeDescriptor::~ColumnTypeDescriptor() {
	delete this->typeName;
	delete this->length;
}

int ColumnTypeDescriptor::binarySize() const {
}

void ColumnTypeDescriptor::toBinary(ByteBuffer* out) {
}

void ColumnTypeDescriptor::fromBinary(ByteBuffer* in) {
}

void ColumnTypeDescriptor::setTypeName(UnicodeString* typeName) noexcept {
	this->typeName = typeName;
}

void ColumnTypeDescriptor::setLength(AbstractSQLExpression* length) noexcept {
	this->length = length;
}

} /* namespace alinous */
