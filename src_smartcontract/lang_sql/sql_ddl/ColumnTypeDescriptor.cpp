/*
 * ColumnTypeDescriptor.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl/ColumnTypeDescriptor.h"

#include "lang_sql/sql/AbstractSQLExpression.h"

#include "base/UnicodeString.h"
#include "base/StackRelease.h"

#include "schema_table/record/table_record_value/AbstractCdbValue.h"


using namespace codablecash;

namespace alinous {

const UnicodeString ColumnTypeDescriptor::TYPE_BYTE(L"byte");
const UnicodeString ColumnTypeDescriptor::TYPE_SHORT(L"short");
const UnicodeString ColumnTypeDescriptor::TYPE_INT(L"int");
const UnicodeString ColumnTypeDescriptor::TYPE_LONG(L"long");
const UnicodeString ColumnTypeDescriptor::TYPE_VARCHAR(L"varchar");
const UnicodeString ColumnTypeDescriptor::TYPE_TEXT(L"text");


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

void ColumnTypeDescriptor::analyze(AnalyzeContext* actx) {
	if(this->length != nullptr){
		this->length->analyze(actx);
	}
}

void ColumnTypeDescriptor::setTypeName(UnicodeString* typeName) noexcept {
	this->typeName = typeName;
}

void ColumnTypeDescriptor::setLength(AbstractSQLExpression* length) noexcept {
	this->length = length;
}

uint8_t ColumnTypeDescriptor::toCdbValueType() const noexcept {
	UnicodeString* lowStr = this->typeName->toLowerCase(); __STP(lowStr);
	uint8_t ret = 0;

	if(lowStr->equals(&ColumnTypeDescriptor::TYPE_BYTE)){
		ret = AbstractCdbValue::TYPE_BYTE;
	}
	else if(lowStr->equals(&ColumnTypeDescriptor::TYPE_SHORT)){
		ret = AbstractCdbValue::TYPE_SHORT;
	}
	else if(lowStr->equals(&ColumnTypeDescriptor::TYPE_INT)){
		ret = AbstractCdbValue::TYPE_INT;
	}
	else if(lowStr->equals(&ColumnTypeDescriptor::TYPE_LONG)){
		ret = AbstractCdbValue::TYPE_LONG;
	}
	else if(lowStr->equals(&ColumnTypeDescriptor::TYPE_VARCHAR) || lowStr->equals(&ColumnTypeDescriptor::TYPE_TEXT)){
		ret = AbstractCdbValue::TYPE_STRING;
	}

	return ret;
}

} /* namespace alinous */
