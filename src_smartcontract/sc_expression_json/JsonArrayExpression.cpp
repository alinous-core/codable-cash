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

#include "instance_dom/DomArrayVariable.h"

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
	return AnalyzedType(AnalyzedType::TYPE_DOM_ARRAY);
}

void JsonArrayExpression::init(VirtualMachine* vm) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->elements->get(i);

		exp->init(vm);
	}
}

AbstractVmInstance* JsonArrayExpression::interpret(VirtualMachine* vm) {
	DomArrayVariable* arrayInst = new(vm) DomArrayVariable(vm);


	return arrayInst;
}

int JsonArrayExpression::binarySize() const {
	int total = sizeof(uint16_t);

	int maxLoop = this->elements->size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->elements->get(i);

		total += exp->binarySize();
	}

	return total;
}

void JsonArrayExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_JSON_ARRAY);

	int maxLoop = this->elements->size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->elements->get(i);

		exp->toBinary(out);
	}
}

void JsonArrayExpression::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = CodeElement::createFromBinary(in);
		checkIsExp(element);

		AbstractExpression* exp = dynamic_cast<AbstractExpression*>(element);
		addElement(exp);
	}
}

} /* namespace alinous */
