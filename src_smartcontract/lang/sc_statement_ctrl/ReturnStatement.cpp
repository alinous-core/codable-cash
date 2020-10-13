/*
 * ReturnStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_statement_ctrl/ReturnStatement.h"
#include "lang/sc_expression/AbstractExpression.h"

#include "vm/vm_ctrl/ExecControlManager.h"
#include "vm/vm_ctrl/ReturnControl.h"

#include "vm/VirtualMachine.h"

#include "vm/variable_access/FunctionArguments.h"

#include "instance/instance_exception/ExceptionInterrupt.h"

namespace alinous {

ReturnStatement::ReturnStatement() : AbstractStatement(CodeElement::STMT_RETURN) {
	this->exp = nullptr;
}

ReturnStatement::~ReturnStatement() {
	delete this->exp;
}

void ReturnStatement::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void ReturnStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void ReturnStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
}


void ReturnStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int alinous::ReturnStatement::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void alinous::ReturnStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_RETURN);
	this->exp->toBinary(out);
}

void alinous::ReturnStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

void ReturnStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

void ReturnStatement::interpret(VirtualMachine* vm) {
	ExecControlManager* ctrl = vm->getCtrl();

	if(this->exp != nullptr){
		interpretExpression(vm);

		if(this->exp->throwsException() && ctrl->isExceptionThrown()){
			return;
		}
	}

	ReturnControl* retCtrl = new ReturnControl();

	ctrl->setInstruction(retCtrl);
}

bool ReturnStatement::hasCtrlStatement() const noexcept {
	return true;
}

void ReturnStatement::interpretExpression(VirtualMachine* vm) {
	try{
		FunctionArguments* args = vm->getFunctionArguments();

		AbstractVmInstance* inst = this->exp->interpret(vm);
		args->setReturnedValue(inst);
	}
	catch(ExceptionInterrupt* e){
		delete e;
	}
}


} /* namespace alinous */
