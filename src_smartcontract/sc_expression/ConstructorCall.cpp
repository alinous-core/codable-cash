/*
 * ConstructorCall.cpp
 *
 *  Created on: 2020/02/05
 *      Author: iizuka
 */

#include "sc_expression/ConstructorCall.h"

#include "sc_analyze/AnalyzedType.h"


namespace alinous {

ConstructorCall::ConstructorCall() : AbstractExpression(CodeElement::EXP_CONSTRUCTORCALL) {
	this->name = nullptr;

}

ConstructorCall::~ConstructorCall() {
	delete this->name;
	this->args.deleteElements();
}

void ConstructorCall::setName(AbstractExpression* exp) noexcept {
	this->name = exp;
}

void ConstructorCall::addArgument(AbstractExpression* exp) noexcept {
	this->args.addElement(exp);
}

int ConstructorCall::binarySize() const {
}

void ConstructorCall::toBinary(ByteBuffer* out) {
}

void ConstructorCall::fromBinary(ByteBuffer* in) {
}

void ConstructorCall::preAnalyze(AnalyzeContext* actx) {
}

void ConstructorCall::analyzeTypeRef(AnalyzeContext* actx) {
}

void ConstructorCall::analyze(AnalyzeContext* actx) {
}

AnalyzedType ConstructorCall::getType(AnalyzeContext* actx) {
}

void ConstructorCall::init(VirtualMachine* vm) {
}

AbstractVmInstance* ConstructorCall::interpret(VirtualMachine* vm) {
}

} /* namespace alinous */
