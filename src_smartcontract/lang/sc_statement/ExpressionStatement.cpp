/*
 * ExpressionStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_statement/ExpressionStatement.h"

#include "lang/sc_expression/AbstractExpression.h"
#include "lang/sc_expression/FunctionCallExpression.h"

#include "instance/instance_gc/GcManager.h"

#include "vm/VirtualMachine.h"

#include "instance/AbstractVmInstance.h"

#include "instance/instance_exception/ExceptionInterrupt.h"


namespace alinous {

ExpressionStatement::ExpressionStatement() : AbstractStatement(CodeElement::STMT_EXPRESSION) {
	this->exp = nullptr;
	this->bctrl = false;
}

ExpressionStatement::~ExpressionStatement() {
	delete this->exp;
}

void ExpressionStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void ExpressionStatement::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void ExpressionStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
	this->bctrl = this->exp->throwsException();
}

void ExpressionStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int ExpressionStatement::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void ExpressionStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_EXPRESSION);
	this->exp->toBinary(out);
}

void ExpressionStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

void ExpressionStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

void ExpressionStatement::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	AbstractVmInstance* retInst = nullptr;
	try{
		retInst = this->exp->interpret(vm);
		gc->handleFloatingObject(retInst != nullptr ? retInst->getInstance() : nullptr);
	}
	catch(ExceptionInterrupt* e){
		delete e;
	}
}

bool ExpressionStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
}

bool ExpressionStatement::hasConstructor() const noexcept {
	short kind = this->exp->getKind();
	if(CodeElement::EXP_FUNCTIONCALL == kind){
		FunctionCallExpression* funcCall = dynamic_cast<FunctionCallExpression*>(this->exp);
		return funcCall->isSuperConstructorCall();
	}

	return false;
}

} /* namespace alinous */
