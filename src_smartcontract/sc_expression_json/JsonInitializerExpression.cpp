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
	int total = sizeof(uint16_t);

	int maxLoop = this->elements->size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		AbstractJsonExpression* exp = this->elements->get(i);

		total += exp->binarySize();
	}

	return total;
}

void JsonInitializerExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_JSON_INITIALIZER);

	int maxLoop = this->elements->size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractJsonExpression* exp = this->elements->get(i);

		exp->toBinary(out);
	}
}

void JsonInitializerExpression::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = CodeElement::createFromBinary(in);
		checkIsJsonExp(element);

		AbstractJsonExpression* exp = dynamic_cast<AbstractJsonExpression*>(element);
		addElement(exp);
	}
}

} /* namespace alinous */
