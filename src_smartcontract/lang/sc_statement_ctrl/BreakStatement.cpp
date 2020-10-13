/*
 * BreakStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_statement_ctrl/BreakStatement.h"

#include "vm/vm_ctrl/ExecControlManager.h"
#include "vm/vm_ctrl/BreakControl.h"

#include "vm/VirtualMachine.h"


namespace alinous {

BreakStatement::BreakStatement() : AbstractStatement(CodeElement::STMT_BREAK) {

}

BreakStatement::~BreakStatement() {
}

void BreakStatement::preAnalyze(AnalyzeContext* actx) {
}

void BreakStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void BreakStatement::analyze(AnalyzeContext* actx) {
}

void BreakStatement::init(VirtualMachine* vm) {
}

int BreakStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void BreakStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::STMT_BREAK);
}

void BreakStatement::fromBinary(ByteBuffer* in) {
}

void BreakStatement::interpret(VirtualMachine* vm) {
	ExecControlManager* ctrl = vm->getCtrl();
	BreakControl* retCtrl = new BreakControl();

	ctrl->setInstruction(retCtrl);
}

bool BreakStatement::hasCtrlStatement() const noexcept {
	return true;
}

} /* namespace alinous */
