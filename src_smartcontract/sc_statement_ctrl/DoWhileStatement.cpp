/*
 * DoWhileStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/DoWhileStatement.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

DoWhileStatement::DoWhileStatement() : AbstractStatement(CodeElement::STMT_DO_WHILE) {
	this->exp = nullptr;
	this->stmt = nullptr;
}

DoWhileStatement::~DoWhileStatement() {
	delete this->exp;
	delete this->stmt;
}

void DoWhileStatement::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);

	this->stmt->setParent(this);
	this->stmt->preAnalyze(actx);
}

void DoWhileStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
	this->stmt->analyzeTypeRef(actx);
}


void alinous::DoWhileStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
	this->stmt->analyze(actx);
}

void DoWhileStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

void DoWhileStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

int DoWhileStatement::binarySize() const {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();
	total += this->stmt->binarySize();

	return total;
}

void DoWhileStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);
	checkNotNull(this->stmt);

	out->putShort(CodeElement::STMT_DO_WHILE);
	this->exp->toBinary(out);
	this->stmt->toBinary(out);
}

void DoWhileStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsStatement(element);
	this->stmt = dynamic_cast<AbstractStatement*>(element);
}

void DoWhileStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
	this->stmt->init(vm);
}

void DoWhileStatement::interpret(VirtualMachine* vm) {
	// FIXME statement
}

} /* namespace alinous */
