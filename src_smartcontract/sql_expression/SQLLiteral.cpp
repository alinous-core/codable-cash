/*
 * SQLLiteral.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLLiteral.h"

#include "base/UnicodeString.h"
#include "base/Long.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_ref/PrimitiveReference.h"

#include "instance_string/VmStringInstance.h"

namespace alinous {

SQLLiteral::SQLLiteral() : AbstractSQLExpression(CodeElement::SQL_EXP_LITERAL) {
	this->value = nullptr;
	this->type = TYPE_STRING;
	this->longv = 0;
}

SQLLiteral::~SQLLiteral() {
	delete this->value;
}

void SQLLiteral::setValue(UnicodeString* value, uint8_t type) noexcept {
	this->value = value;
	this->type = type;
}

int SQLLiteral::binarySize() const {
	checkNotNull(this->value);

	int total = sizeof(uint16_t);
	total += stringSize(this->value);
	total += sizeof(uint8_t);

	return total;
}

void SQLLiteral::toBinary(ByteBuffer* out) {
	checkNotNull(this->value);

	out->putShort(CodeElement::SQL_EXP_LITERAL);
	putString(out, this->value);
	out->put(this->type);
}

void SQLLiteral::fromBinary(ByteBuffer* in) {
	this->value = getString(in);
	this->type = in->get();
}

void SQLLiteral::preAnalyze(AnalyzeContext* actx) {
}

void SQLLiteral::analyzeTypeRef(AnalyzeContext* actx) {
}

void SQLLiteral::analyze(AnalyzeContext* actx) {
	if(this->type == SQLLiteral::TYPE_NUMBER){
		this->longv = Long::parseLong(this->value);
	}
}

AnalyzedType SQLLiteral::getType(AnalyzeContext* actx) {
	if(this->type == SQLLiteral::TYPE_NUMBER){
		return AnalyzedType(AnalyzedType::TYPE_LONG);
	}

	return AnalyzedType(AnalyzedType::TYPE_STRING);
}

void SQLLiteral::init(VirtualMachine* vm) {
}

AbstractVmInstance* SQLLiteral::interpret(VirtualMachine* vm) {
	if(this->type == SQLLiteral::TYPE_NUMBER){
		return PrimitiveReference::createLongReference(vm, this->longv);
	}

	VmStringInstance* inst = new(vm) VmStringInstance(vm, this->value);
	return inst;
}


} /* namespace alinous */
