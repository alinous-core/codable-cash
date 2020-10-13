/*
 * JsonInitializer.cpp
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#include "lang/sc_expression_json/JsonInitializerExpression.h"
#include "lang/sc_expression_json/JsonKeyValuePairExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/AnalyzeContext.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"

#include "instance/instance_dom/DomVariableInstance.h"

#include "instance/instance_gc/StackFloatingVariableHandler.h"

#include "instance/instance_dom/DomRuntimeReference.h"

#include "instance/instance_string/VmStringInstance.h"
namespace alinous {

JsonInitializerExpression::JsonInitializerExpression() : AbstractJsonExpression(CodeElement::EXP_JSON_INITIALIZER) {
	this->elements = new ArrayList<JsonKeyValuePairExpression>();
}

JsonInitializerExpression::~JsonInitializerExpression() {
	this->elements->deleteElements();
	delete this->elements;
}

void JsonInitializerExpression::addElement(JsonKeyValuePairExpression* element) noexcept {
	this->elements->addElement(element);
}

void JsonInitializerExpression::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		JsonKeyValuePairExpression* exp = this->elements->get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void JsonInitializerExpression::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		JsonKeyValuePairExpression* exp = this->elements->get(i);

		exp->analyzeTypeRef(actx);
	}
}

void JsonInitializerExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		JsonKeyValuePairExpression* exp = this->elements->get(i);

		exp->analyze(actx);
	}
}

AnalyzedType JsonInitializerExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_DOM);
}

void JsonInitializerExpression::init(VirtualMachine* vm) {
	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		JsonKeyValuePairExpression* exp = this->elements->get(i);

		exp->init(vm);
	}
}

AbstractVmInstance* JsonInitializerExpression::interpret(VirtualMachine* vm) {
	StackFloatingVariableHandler releaser(vm->getGc());

	DomVariableInstance* inst = new(vm) DomVariableInstance(vm);

	int maxLoop = this->elements->size();
	for(int i = 0; i != maxLoop; ++i){
		JsonKeyValuePairExpression* exp = this->elements->get(i);

		const UnicodeString* name = exp->getName();

		AbstractVmInstance* valueInst = exp->interpret(vm);
		releaser.registerInstance(valueInst);

		VmStringInstance* vmstr = new(vm) VmStringInstance(vm, name);
		releaser.registerInstance(vmstr);

		inst->putProperty(vm, vmstr, valueInst != nullptr ? valueInst->getInstance() : nullptr);
	}

	return inst;
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

		JsonKeyValuePairExpression* exp = dynamic_cast<JsonKeyValuePairExpression*>(element);
		addElement(exp);
	}
}

} /* namespace alinous */
