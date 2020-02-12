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

namespace alinous {

ConstructorArray::ConstructorArray() : AbstractExpression(CodeElement::EXP_CONSTRUCTORARRAY) {
	this->valId = nullptr;
}

ConstructorArray::~ConstructorArray() {
	delete this->valId;
	this->dims.deleteElements();
}

int ConstructorArray::binarySize() const {
}

void ConstructorArray::toBinary(ByteBuffer* out) {
	checkNotNull(this->valId);
}

void ConstructorArray::fromBinary(ByteBuffer* in) {
}

void ConstructorArray::preAnalyze(AnalyzeContext* actx) {
}

void ConstructorArray::analyzeTypeRef(AnalyzeContext* actx) {
}

void ConstructorArray::analyze(AnalyzeContext* actx) {
}

AnalyzedType ConstructorArray::getType(AnalyzeContext* actx) {
}

void ConstructorArray::init(VirtualMachine* vm) {
}

AbstractVmInstance* ConstructorArray::interpret(VirtualMachine* vm) {
}

void ConstructorArray::setValId(VariableIdentifier* valId) noexcept {
	this->valId = valId;
}

void ConstructorArray::addDim(NumberLiteral* dim) noexcept {
	this->dims.addElement(dim);
}

} /* namespace alinous */
