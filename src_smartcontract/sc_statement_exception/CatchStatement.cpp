/*
 * CatchStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/CatchStatement.h"

#include "sc_statement/StatementBlock.h"
#include "sc_statement/VariableDeclareStatement.h"


namespace alinous {

CatchStatement::CatchStatement() : AbstractStatement(CodeElement::STMT_TRY_CATCH) {
	this->block = nullptr;
	this->variableDeclare = nullptr;
}

CatchStatement::~CatchStatement() {
	delete this->block;
	delete this->variableDeclare;
}

void CatchStatement::preAnalyze(AnalyzeContext* actx) {
}

void CatchStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void CatchStatement::analyze(AnalyzeContext* actx) {
}

void CatchStatement::init(VirtualMachine* vm) {
}

void CatchStatement::interpret(VirtualMachine* vm) {
}

bool CatchStatement::hasCtrlStatement() const noexcept {
	return true;
}

int CatchStatement::binarySize() const {
}

void CatchStatement::toBinary(ByteBuffer* out) {
}

void CatchStatement::fromBinary(ByteBuffer* in) {
}

void CatchStatement::setBlock(StatementBlock* block) noexcept {
	this->block = block;
}

void CatchStatement::setVariableDeclare(VariableDeclareStatement* variableDeclare) noexcept {
	this->variableDeclare = variableDeclare;
}

} /* namespace alinous */
