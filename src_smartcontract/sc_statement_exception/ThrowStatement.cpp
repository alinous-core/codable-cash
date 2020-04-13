/*
 * ThrowStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/ThrowStatement.h"

namespace alinous {

ThrowStatement::ThrowStatement() : AbstractStatement(CodeElement::STMT_THROW) {

}

ThrowStatement::~ThrowStatement() {

}

void ThrowStatement::preAnalyze(AnalyzeContext* actx) {
}

void ThrowStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void ThrowStatement::analyze(AnalyzeContext* actx) {
}

void ThrowStatement::init(VirtualMachine* vm) {
}

void ThrowStatement::interpret(VirtualMachine* vm) {
}

bool ThrowStatement::hasCtrlStatement() const noexcept {
	return true;
}

int ThrowStatement::binarySize() const {
}

void ThrowStatement::toBinary(ByteBuffer* out) {
}

void ThrowStatement::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
