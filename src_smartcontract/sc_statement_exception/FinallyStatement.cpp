/*
 * FinallyStatement.cpp
 *
 *  Created on: 2020/04/15
 *      Author: iizuka
 */

#include "sc_statement_exception/FinallyStatement.h"

#include "sc_statement/StatementBlock.h"


namespace alinous {

FinallyStatement::FinallyStatement() : AbstractStatement(CodeElement::STMT_FINALLY) {
	this->block = nullptr;
}

FinallyStatement::~FinallyStatement() {
	delete this->block;
}

void FinallyStatement::preAnalyze(AnalyzeContext* actx) {
}

void FinallyStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void FinallyStatement::analyze(AnalyzeContext* actx) {
}

void FinallyStatement::init(VirtualMachine* vm) {
}

void FinallyStatement::interpret(VirtualMachine* vm) {
}

bool FinallyStatement::hasCtrlStatement() const noexcept {
}

int FinallyStatement::binarySize() const {
}

void FinallyStatement::toBinary(ByteBuffer* out) {
}

void FinallyStatement::fromBinary(ByteBuffer* in) {
}

void FinallyStatement::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

} /* namespace alinous */
