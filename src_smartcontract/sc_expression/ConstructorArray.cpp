/*
 * ConstructorArray.cpp
 *
 *  Created on: 2020/02/12
 *      Author: iizuka
 */

#include "sc_expression/ConstructorArray.h"

#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/AnalyzedType.h"

#include "instance/AbstractVmInstance.h"

#include "vm/VirtualMachine.h"

#include "base_io/ByteBuffer.h"

#include "sc_expression/VariableIdentifier.h"
#include "sc_expression/NumberLiteral.h"

#include "sc_analyze/AnalyzedThisClassStackPopper.h"
namespace alinous {

ConstructorArray::ConstructorArray() : AbstractExpression(CodeElement::EXP_CONSTRUCTORARRAY) {
	this->valId = nullptr;
	this->atype = nullptr;
}

ConstructorArray::~ConstructorArray() {
	delete this->valId;
	this->dims.deleteElements();
	delete this->atype;
}

int ConstructorArray::binarySize() const {
	checkNotNull(this->valId);

	int total = sizeof(uint16_t);
	total += this->valId->binarySize();

	int maxLoop = this->dims.size();
	total += sizeof(int32_t);

	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->dims.get(i);
		total += exp->binarySize();
	}

	return total;
}

void ConstructorArray::toBinary(ByteBuffer* out) {
	checkNotNull(this->valId);

	out->putShort(CodeElement::EXP_CONSTRUCTORARRAY);

	int maxLoop = this->dims.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->dims.get(i);
		exp->toBinary(out);
	}
}

void ConstructorArray::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_VARIABLE_ID);
	this->valId = dynamic_cast<VariableIdentifier*>(element);

	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		element = createFromBinary(in);
		checkKind(element, CodeElement::EXP_NUMBER_LITERAL);

		AbstractExpression* exp = dynamic_cast<NumberLiteral*>(element);
		this->dims.addElement(exp);
	}
}

void ConstructorArray::preAnalyze(AnalyzeContext* actx) {
	this->valId->preAnalyze(actx);

	int maxLoop = this->dims.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->dims.get(i);
		exp->preAnalyze(actx);
	}
}

void ConstructorArray::analyzeTypeRef(AnalyzeContext* actx) {
	this->valId->analyzeTypeRef(actx);

	int maxLoop = this->dims.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->dims.get(i);
		exp->analyzeTypeRef(actx);
	}
}

void ConstructorArray::analyze(AnalyzeContext* actx) {
	{
		int maxLoop = this->dims.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractExpression* exp = this->dims.get(i);
			exp->analyze(actx);
		}
	}

	this->atype = new AnalyzedType(*actx->getTmpArrayType());
	int dim = this->dims.size();
	this->atype->setDim(dim);
}

AnalyzedType ConstructorArray::getType(AnalyzeContext* actx) {
	return *this->atype;
}

void ConstructorArray::init(VirtualMachine* vm) {
	this->valId->init(vm);

	int maxLoop = this->dims.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->dims.get(i);
		exp->init(vm);
	}
}

AbstractVmInstance* ConstructorArray::interpret(VirtualMachine* vm) {
	int dim = this->atype->getDim();

	// FIXME
	return nullptr;
}


void ConstructorArray::setValId(VariableIdentifier* valId) noexcept {
	this->valId = valId;
}

void ConstructorArray::addDim(AbstractExpression* dim) noexcept {
	this->dims.addElement(dim);
}

const UnicodeString* ConstructorArray::getName() const noexcept {
	return this->valId->getName();
}

} /* namespace alinous */
