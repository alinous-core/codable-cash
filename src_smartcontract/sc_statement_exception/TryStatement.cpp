/*
 * TryStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/TryStatement.h"

#include "sc_statement/StatementBlock.h"
#include "sc_statement_exception/CatchStatement.h"


namespace alinous {

TryStatement::TryStatement() : AbstractStatement(CodeElement::STMT_TRY) {
	this->block = nullptr;
	this->catchStmt = nullptr;
}

TryStatement::~TryStatement() {
	delete this->block;
	delete this->catchStmt;
}

void TryStatement::preAnalyze(AnalyzeContext* actx) {
	this->block->setParent(this);
	this->block->preAnalyze(actx);

	this->catchStmt->setParent(this);
	this->catchStmt->preAnalyze(actx);
}

void TryStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->block->analyzeTypeRef(actx);
	this->catchStmt->analyzeTypeRef(actx);
}

void TryStatement::analyze(AnalyzeContext* actx) {
	this->block->analyze(actx);
	this->catchStmt->analyze(actx);
}

void TryStatement::init(VirtualMachine* vm) {
	this->block->init(vm);
	this->catchStmt->init(vm);
}

void TryStatement::interpret(VirtualMachine* vm) {
}

bool TryStatement::hasCtrlStatement() const noexcept {
	return true;
}

int TryStatement::binarySize() const {
	checkNotNull(this->block);
	checkNotNull(this->catchStmt);

	int total = sizeof(uint16_t);

	total += this->block->binarySize();
	total += this->catchStmt->binarySize();

	return total;
}

void TryStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->block);
	checkNotNull(this->catchStmt);

	out->putShort(CodeElement::STMT_TRY);

	this->block->toBinary(out);
	this->catchStmt->toBinary(out);
}

void TryStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::STMT_BLOCK);

	this->block = dynamic_cast<StatementBlock*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::STMT_TRY_CATCH);

	this->catchStmt = dynamic_cast<CatchStatement*>(element);
}

void TryStatement::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

void TryStatement::setCatchStatement(CatchStatement* catchStmt) noexcept {
	this->catchStmt = catchStmt;
}

} /* namespace alinous */
