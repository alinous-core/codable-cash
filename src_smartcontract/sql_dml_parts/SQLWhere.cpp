/*
 * SQLWhere.cpp
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#include "sql_dml_parts/SQLWhere.h"
#include "sql/AbstractSQLExpression.h"

namespace alinous {

SQLWhere::SQLWhere() : AbstractSQLPart(CodeElement::SQL_PART_WHERE) {
	this->exp = nullptr;
}

SQLWhere::~SQLWhere() {
	delete this->exp;
}

void alinous::SQLWhere::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

void SQLWhere::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SQLWhere::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void SQLWhere::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

void SQLWhere::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* SQLWhere::interpret(VirtualMachine* vm) {
	this->exp->interpret(vm);

	return nullptr;
}

int SQLWhere::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLWhere::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_PART_WHERE);
	this->exp->toBinary(out);
}

void SQLWhere::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

} /* namespace alinous */
