/*
 * SubstitutionStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement/SubstitutionStatement.h"
#include "sc_expression/VariableIdentifier.h"
#include "sc_expression/AbstractExpression.h"

#include "instance/AbstractVmInstance.h"

#include "instance_ref/AbstractReference.h"

#include "instance_gc/GcManager.h"

#include "type_check/AnalyzedTypeChecker.h"

#include "instance_gc/StackFloatingVariableHandler.h"

#include "instance/IAbstractVmInstanceSubstance.h"

#include "sc_analyze/AnalyzeContext.h"


namespace alinous {

SubstitutionStatement::SubstitutionStatement() : AbstractStatement(CodeElement::STMT_SUBSTITUTION) {
	this->variable = nullptr;
	this->exp = nullptr;
	this->bctrl = false;
}

SubstitutionStatement::~SubstitutionStatement() {
	delete this->variable;
	delete this->exp;
}

void SubstitutionStatement::preAnalyze(AnalyzeContext* actx) {
	this->variable->setParent(this);
	this->variable->preAnalyze(actx);

	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SubstitutionStatement::analyzeTypeRef(AnalyzeContext* actx) {
	this->variable->analyzeTypeRef(actx);
	this->exp->analyzeTypeRef(actx);
}

void SubstitutionStatement::analyze(AnalyzeContext* actx) {
	AnalyzedTypeChecker typeChecker;

	this->variable->analyze(actx);
	this->exp->analyze(actx);

	if(!actx->hasError()){
		bool result = typeChecker.checkCompatibility(actx, this->variable, this->exp);
	}

	this->bctrl = this->variable->throwsException() || this->exp->throwsException();
}

void SubstitutionStatement::setVariableId(AbstractExpression* variable) noexcept {
	this->variable = variable;
}


void SubstitutionStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int SubstitutionStatement::binarySize() const {
	checkNotNull(this->variable);
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->variable->binarySize();
	total += this->exp->binarySize();

	return total;
}

void SubstitutionStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->variable);
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_SUBSTITUTION);
	this->variable->toBinary(out);
	this->exp->toBinary(out);
}

void SubstitutionStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_VARIABLE_ID);
	this->variable = dynamic_cast<VariableIdentifier*>(element);

	element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

void SubstitutionStatement::init(VirtualMachine* vm) {
	this->variable->init(vm);
	this->exp->init(vm);
}

void SubstitutionStatement::interpret(VirtualMachine* vm) {
	AbstractVmInstance* leftValue = this->variable->interpret(vm);
	AbstractVmInstance* rightValue = this->exp->interpret(vm);

	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);
	releaser.registerInstance(rightValue);

	AbstractReference* leftRef = dynamic_cast<AbstractReference*>(leftValue);
	assert(leftRef->isReference());


	IAbstractVmInstanceSubstance* sub = nullptr;
	if(rightValue != nullptr){
		sub = rightValue->getInstance();
	}

	leftRef->substitute(sub, vm);
}

bool SubstitutionStatement::hasCtrlStatement() const noexcept {
	return this->bctrl;
}


} /* namespace alinous */
