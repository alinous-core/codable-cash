/*
 * ForStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement_ctrl/ForStatement.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

ForStatement::ForStatement() : AbstractStatement(CodeElement::STMT_FOR) {
	this->stmt = nullptr;
	this->init = nullptr;
	this->cond = nullptr;
	this->postLoop = nullptr;
}

ForStatement::~ForStatement() {
	delete this->stmt;
	delete this->init;
	delete this->cond;
	delete this->postLoop;
}

void ForStatement::preAnalyze(AnalyzeContext* actx) {
	// FIXME
}

void ForStatement::analyze(AnalyzeContext* actx) {
	// FIXME
}

void ForStatement::setStatement(AbstractStatement* stmt) noexcept {
	this->stmt = stmt;
}

void ForStatement::setInit(AbstractStatement* init) noexcept {
	this->init = init;
}

void ForStatement::setCondition(AbstractExpression* cond) noexcept {
	this->cond = cond;
}

void ForStatement::setPostLoop(AbstractExpression* postLoop) noexcept {
	this->postLoop = postLoop;
}

int ForStatement::binarySize() const {
	checkNotNull(this->stmt);
	checkNotNull(this->init);
	checkNotNull(this->cond);
	checkNotNull(this->postLoop);

	int total = sizeof(uint16_t);
	total += this->stmt->binarySize();
	total += this->init->binarySize();
	total += this->cond->binarySize();
	total += this->postLoop->binarySize();

	return total;
}

void ForStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->stmt);
	checkNotNull(this->init);
	checkNotNull(this->cond);
	checkNotNull(this->postLoop);

	out->putShort(CodeElement::STMT_FOR);
	this->stmt->toBinary(out);
	this->init->toBinary(out);
	this->cond->toBinary(out);
	this->postLoop->toBinary(out);
}

void ForStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsStatement(element);
	this->stmt = dynamic_cast<AbstractStatement*>(element);

	element = createFromBinary(in);
	checkIsStatement(element);
	this->init = dynamic_cast<AbstractStatement*>(element);

	element = createFromBinary(in);
	checkIsExp(element);
	this->cond = dynamic_cast<AbstractExpression*>(element);

	element = createFromBinary(in);
	checkIsExp(element);
	this->postLoop = dynamic_cast<AbstractExpression*>(element);
}

} /* namespace alinous */
