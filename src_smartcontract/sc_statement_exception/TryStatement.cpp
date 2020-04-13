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
}

void TryStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void TryStatement::analyze(AnalyzeContext* actx) {
}

void TryStatement::init(VirtualMachine* vm) {
}

void TryStatement::interpret(VirtualMachine* vm) {
}

bool TryStatement::hasCtrlStatement() const noexcept {
	return true;
}

int TryStatement::binarySize() const {
}

void TryStatement::toBinary(ByteBuffer* out) {
}

void TryStatement::fromBinary(ByteBuffer* in) {
}

void TryStatement::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

void TryStatement::setCatchStatement(CatchStatement* catchStmt) noexcept {
	this->catchStmt = catchStmt;
}

} /* namespace alinous */
