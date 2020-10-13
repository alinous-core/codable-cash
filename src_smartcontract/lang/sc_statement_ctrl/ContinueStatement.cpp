/*
 * ContinueStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_statement_ctrl/ContinueStatement.h"

#include "vm/vm_ctrl/ExecControlManager.h"
#include "vm/vm_ctrl/ContinueControl.h"

#include "vm/VirtualMachine.h"


namespace alinous {

ContinueStatement::ContinueStatement() : AbstractStatement(CodeElement::STMT_CONTINUE) {

}

ContinueStatement::~ContinueStatement() {
}

void ContinueStatement::preAnalyze(AnalyzeContext* actx) {
}

void ContinueStatement::analyzeTypeRef(AnalyzeContext* actx) {
}

void ContinueStatement::analyze(AnalyzeContext* actx) {
}

int ContinueStatement::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void ContinueStatement::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::STMT_CONTINUE);
}

void ContinueStatement::fromBinary(ByteBuffer* in) {
}

void ContinueStatement::init(VirtualMachine* vm) {
}

void ContinueStatement::interpret(VirtualMachine* vm) {
	ExecControlManager* ctrl = vm->getCtrl();
	ContinueControl* retCtrl = new ContinueControl();

	ctrl->setInstruction(retCtrl);
}

bool ContinueStatement::hasCtrlStatement() const noexcept {
	return true;
}

} /* namespace alinous */
