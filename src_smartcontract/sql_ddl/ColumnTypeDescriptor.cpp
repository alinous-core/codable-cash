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
	checkNotNull(this->typeName);

	int total = sizeof(uint16_t);

	total += stringSize(this->typeName);
	total += sizeof(int8_t);

	if(this->length != nullptr){
		total += this->length->binarySize();
	}

	return total;
}

void ColumnTypeDescriptor::toBinary(ByteBuffer* out) {
	checkNotNull(this->typeName);

	out->putShort(CodeElement::DDL_TYPE_DESC);

	putString(out, this->typeName);

	bool bl = this->length != nullptr;
	out->put(bl ? 1 : 0);

	if(bl){
		this->length->toBinary(out);
	}
}

void ColumnTypeDescriptor::fromBinary(ByteBuffer* in) {
	this->typeName = getString(in);

	int8_t bl = in->get();
	if(bl > 0){
		CodeElement* element = createFromBinary(in);
		checkIsSQLExp(element);

		this->length = dynamic_cast<AbstractSQLExpression*>(element);
	}
}

void ColumnTypeDescriptor::setTypeName(UnicodeString* typeName) noexcept {
	this->typeName = typeName;
}

void ColumnTypeDescriptor::setLength(AbstractSQLExpression* length) noexcept {
	this->length = length;
}

} /* namespace alinous */
