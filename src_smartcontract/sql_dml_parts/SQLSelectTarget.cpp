/*
 * SQLSelectTarget.cpp
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLSelectTarget.h"
#include "base/UnicodeString.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLSelectTarget::SQLSelectTarget() : AbstractSQLPart(CodeElement::SQL_PART_SELECT_TARGET) {
	this->wildcard = false;
	this->exp = nullptr;
	this->asName = nullptr;
}

SQLSelectTarget::~SQLSelectTarget() {
	delete this->exp;
	delete this->asName;
}

void SQLSelectTarget::setWildcard(bool wildcard) noexcept {
	this->wildcard = wildcard;
}

void SQLSelectTarget::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

void SQLSelectTarget::setAsName(UnicodeString* asName) noexcept {
	this->asName = asName;
}

void SQLSelectTarget::preAnalyze(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->setParent(this);
		this->exp->preAnalyze(actx);
	}
}

void SQLSelectTarget::analyzeTypeRef(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->analyzeTypeRef(actx);
	}
}

void SQLSelectTarget::analyze(AnalyzeContext* actx) {
	if(this->exp != nullptr){
		this->exp->analyze(actx);
	}
}

void SQLSelectTarget::init(VirtualMachine* vm) {
	if(this->exp != nullptr){
		this->exp->init(vm);
	}
}

AbstractVmInstance* SQLSelectTarget::interpret(VirtualMachine* vm) {
	if(this->wildcard){

	}

	// FIXME SQLSelectTarget::interpret()
}

int SQLSelectTarget::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint8_t);
	total += sizeof(uint8_t);
	if(this->exp != nullptr){
		total += this->exp->binarySize();
	}

	total += sizeof(uint8_t);
	if(this->asName != nullptr){
		total += stringSize(this->asName);
	}

	return total;
}

void SQLSelectTarget::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_PART_SELECT_TARGET);

	out->put(this->wildcard ? 1 : 0);
	out->put(this->exp != nullptr ? 1 : 0);
	if(this->exp != nullptr){
		this->exp->toBinary(out);
	}

	out->put(this->asName != nullptr ? 1 : 0);
	if(this->asName != nullptr){
		putString(out, this->asName);
	}
}

void SQLSelectTarget::fromBinary(ByteBuffer* in) {
	int8_t bl = in->get();
	this->wildcard = (bl == 1);

	bl = in->get();
	if(bl == 1){
		CodeElement* element = createFromBinary(in);
		checkIsSQLExp(element);
		this->exp = dynamic_cast<AbstractSQLExpression*>(element);
	}

	bl = in->get();
	if(bl == 1){
		this->asName = getString(in);
	}
}

} /* namespace alinous */
