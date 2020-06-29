/*
 * JsonInitializer.cpp
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#include "sc_expression_json/JsonInitializerExpression.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"

namespace alinous {

JsonInitializerExpression::JsonInitializerExpression() : AbstractJsonExpression(CodeElement::EXP_JSON_INITIALIZER) {
	this->elements = new ArrayList<AbstractJsonExpression>();
}

JsonInitializerExpression::~JsonInitializerExpression() {
	delete this->elements;
}

void JsonInitializerExpression::addElement(AbstractJsonExpression* element) noexcept {
	this->elements->addElement(element);
}

void JsonInitializerExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJsonExpression* exp = this->elements->get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void JsonInitializerExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJsonExpression* exp = this->elements->get(i);

		exp->analyzeTypeRef(actx);
	}
}

void JsonInitializerExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJsonExpression* exp = this->elements->get(i);

		exp->analyze(actx);
	}
}

AnalyzedType JsonInitializerExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_DOM);
}

void JsonInitializerExpression::init(VirtualMachine* vm) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractJsonExpression* exp = this->elements->get(i);

		exp->init(vm);
	}
}

AbstractVmInstance* JsonInitializerExpression::interpret(VirtualMachine* vm) {
}

int JsonInitializerExpression::binarySize() const {

}

void JsonInitializerExpression::toBinary(ByteBuffer* out) {
}

void JsonInitializerExpression::fromBinary(ByteBuffer* in) {
}

} /* namespace alinous */
