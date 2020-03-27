/*
 * ConditionalAndExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression_logical/ConditionalAndExpression.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/ValidationError.h"

#include "instance_gc/GcManager.h"

#include "vm/VirtualMachine.h"

#include "instance_ref/PrimitiveReference.h"

namespace alinous {

ConditionalAndExpression::ConditionalAndExpression() : AbstractBinaryExpression(CodeElement::EXP_CND_AND) {
}

ConditionalAndExpression::~ConditionalAndExpression() {
}

void ConditionalAndExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void ConditionalAndExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyzeTypeRef(actx);
}

void ConditionalAndExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* expression = this->list.get(i);
		AnalyzedType at = expression->getType(actx);

		if(!at.isBool()){
			actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"Logical expression requires boolean parameter.", {});
		}
	}
}

int ConditionalAndExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void ConditionalAndExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_CND_AND);
	AbstractBinaryExpression::toBinary(out);
}

void ConditionalAndExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType ConditionalAndExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

AbstractVmInstance* ConditionalAndExpression::interpret(VirtualMachine* vm) {
	GcManager* gc = vm->getGc();

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);

		AbstractVmInstance* inst = exp->interpret(vm);
		PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);

		int32_t val = ref->getIntValue();
		gc->handleFloatingObject(inst != nullptr ? inst->getInstance() : nullptr);

		if(val < 1){
			return PrimitiveReference::createBoolReference(vm, 0);
		}
	}

	return PrimitiveReference::createBoolReference(vm, 1);
}

} /* namespace alinous */
