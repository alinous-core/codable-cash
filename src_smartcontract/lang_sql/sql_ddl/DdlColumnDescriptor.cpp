/*
 * DdlColumnDescriptor.cpp
 *
 *  Created on: 2020/05/09
 *      Author: iizuka
 */

#include "lang_sql/sql_ddl/DdlColumnDescriptor.h"

#include "base/UnicodeString.h"

#include "lang_sql/sql_ddl/ColumnTypeDescriptor.h"

#include "lang_sql/sql/AbstractSQLExpression.h"

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
	checkNotNull(this->name);
	checkNotNull(this->typeDesc);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);
	total += this->typeDesc->binarySize();

	total += sizeof(int8_t); // notNull
	total += sizeof(int8_t); // unique

	total += sizeof(int8_t);
	if(this->defaultValue != nullptr){
		total += this->defaultValue->binarySize();
	}

	return total;
}

void DdlColumnDescriptor::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);
	checkNotNull(this->typeDesc);

	out->putShort(CodeElement::DDL_COLMUN_DESC);

	putString(out, this->name);
	this->typeDesc->toBinary(out);

	out->put(this->notNull ? 1 : 0);
	out->put(this->unique ? 1 : 0);

	bool bl = this->defaultValue != nullptr;
	out->put(bl ? 1 : 0);
	if(bl){
		this->defaultValue->toBinary(out);
	}
}

void DdlColumnDescriptor::fromBinary(ByteBuffer* in) {
	this->name = getString(in);

	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::DDL_TYPE_DESC);
	this->typeDesc = dynamic_cast<ColumnTypeDescriptor*>(element);

	int8_t bl = in->get();
	this->notNull = bl > 0;

	bl = in->get();
	this->unique = bl > 0;

	bl = in->get();
	if(bl > 0){
		element = createFromBinary(in);
		checkIsSQLExp(element);

		this->defaultValue = dynamic_cast<AbstractSQLExpression*>(element);
	}

}

void DdlColumnDescriptor::analyze(AnalyzeContext* actx) {
	this->typeDesc->analyze(actx);

	if(this->defaultValue != nullptr){
		this->defaultValue->analyze(actx);
	}
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
