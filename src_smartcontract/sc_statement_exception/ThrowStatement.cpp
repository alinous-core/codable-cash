/*
 * ThrowStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/ThrowStatement.h"

#include "sc_expression/AbstractExpression.h"


namespace alinous {

ThrowStatement::ThrowStatement() : AbstractStatement(CodeElement::STMT_THROW) {
	this->exp = nullptr;
}

ThrowStatement::~ThrowStatement() {
	delete this->exp;
}

void ThrowStatement::preAnalyze(AnalyzeContext* actx) {
}

void ThrowStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void ThrowStatement::analyze(AnalyzeContext* actx) {
}

void ThrowStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

void ThrowStatement::interpret(VirtualMachine* vm) {
}

bool ThrowStatement::hasCtrlStatement() const noexcept {
	return true;
}

int ThrowStatement::binarySize() const {
	int total = sizeof(uint16_t);

	total += this->exp->binarySize();

	return total;
}

void ThrowStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_THROW);

	this->exp->toBinary(out);
}

void ThrowStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);

	this->exp = dynamic_cast<AbstractExpression*>(element);
}

void ThrowStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
