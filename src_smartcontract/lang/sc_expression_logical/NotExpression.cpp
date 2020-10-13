/*
 * NotExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "lang/sc_expression_logical/NotExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/ValidationError.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "instance/instance_ref/PrimitiveReference.h"

#include "instance/instance_gc/GcManager.h"
#include "instance/instance_gc/StackFloatingVariableHandler.h"


namespace alinous {

NotExpression::NotExpression() : AbstractExpression(CodeElement::EXP_CND_NOT) {
	this->exp = nullptr;
}

NotExpression::~NotExpression() {
	delete this->exp;
}

void NotExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void NotExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void NotExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	AnalyzedType at = this->exp->getType(actx);
	if(!at.isBool()){
		actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"Logical expression requires boolean parameter.", {});
	}
}

void NotExpression::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

int NotExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void NotExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::EXP_CND_NOT);
	this->exp->toBinary(out);
}

void NotExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

AnalyzedType NotExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void NotExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* NotExpression::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();
	StackFloatingVariableHandler releaser(gc);

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* blRef =dynamic_cast<PrimitiveReference*>(inst);

	bool blvalue = !(blRef->getIntValue() == 1);

	return PrimitiveReference::createBoolReference(vm, blvalue ? 1 : 0);
}

} /* namespace alinous */
