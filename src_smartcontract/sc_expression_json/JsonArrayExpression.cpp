/*
 * JsonArrayExpression.cpp
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#include "sc_expression_json/JsonArrayExpression.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"


namespace alinous {

JsonArrayExpression::JsonArrayExpression() : AbstractJsonExpression(CodeElement::EXP_JSON_ARRAY) {
	this->elements = new ArrayList<AbstractExpression>();
}

JsonArrayExpression::~JsonArrayExpression() {
	this->elements->deleteElements();
	delete this->elements;
}

void JsonArrayExpression::addElement(AbstractExpression* element) noexcept {
	this->elements->addElement(element);
}

void JsonArrayExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->elements->get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void JsonArrayExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->elements->get(i);

		exp->analyzeTypeRef(actx);
	}
}

void JsonArrayExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->elements->get(i);

		exp->analyze(actx);
	}
}

AnalyzedType JsonArrayExpression::getType(AnalyzeContext* actx) {
}

void JsonArrayExpression::init(VirtualMachine* vm) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->elements->get(i);

		exp->init(vm);
	}
}

AbstractVmInstance* JsonArrayExpression::interpret(VirtualMachine* vm) {
}

int JsonArrayExpression::binarySize() const {
}

void JsonArrayExpression::toBinary(ByteBuffer* out) {
}

void JsonArrayExpression::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
