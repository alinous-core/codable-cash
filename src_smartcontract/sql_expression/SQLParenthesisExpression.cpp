/*
 * SQLParenthesisExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLParenthesisExpression.h"

#include "sc_analyze/AnalyzedType.h"
namespace alinous {

SQLParenthesisExpression::SQLParenthesisExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_PARENTHESIS) {
	this->exp = nullptr;
}

SQLParenthesisExpression::~SQLParenthesisExpression() {
	delete this->exp;
}

void SQLParenthesisExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLParenthesisExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLParenthesisExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_EXP_PARENTHESIS);
	this->exp->toBinary(out);
}

void SQLParenthesisExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

void SQLParenthesisExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SQLParenthesisExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void SQLParenthesisExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}

AnalyzedType SQLParenthesisExpression::getType(AnalyzeContext* actx) {
	return this->exp->getType(actx);
}

void SQLParenthesisExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* SQLParenthesisExpression::interpret(VirtualMachine* vm) {
	return this->exp->interpret(vm);
}


} /* namespace alinous */
