/*
 * ThrowStatement.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "sc_statement_exception/ThrowStatement.h"

#include "sc_expression/AbstractExpression.h"

#include "vm/VirtualMachine.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance/AbstractVmInstance.h"


namespace alinous {

ThrowStatement::ThrowStatement() : AbstractStatement(CodeElement::STMT_THROW) {
	this->exp = nullptr;
}

ThrowStatement::~ThrowStatement() {
	delete this->exp;
}

void ThrowStatement::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void ThrowStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void ThrowStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	AnalyzedType atype = this->exp->getType(actx);
	if(atype.isNull()){

	}
	else if(atype.isArray()){

	}
	else if(atype.isBool() || atype.isPrimitiveInteger()){

	}
}

void ThrowStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

void ThrowStatement::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	ExecControlManager* ctrl = vm->getCtrl();

	AbstractVmInstance* inst = this->exp->interpret(vm);
	IAbstractVmInstanceSubstance* sub = inst->getInstance();

}

bool ThrowStatement::hasCtrlStatement() const noexcept {
	return true;
}

int ThrowStatement::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);

	total += this->exp->binarySize();

	return total;
}

void ThrowStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_THROW);

	this->exp->toBinary(out);
}

void ThrowStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);

	this->exp = dynamic_cast<AbstractExpression*>(element);
}

void ThrowStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
