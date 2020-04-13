/*
 * TryStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/TryStatement.h"

namespace alinous {

TryStatement::TryStatement() : AbstractStatement(CodeElement::STMT_TRY) {

}

TryStatement::~TryStatement() {

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

} /* namespace alinous */
