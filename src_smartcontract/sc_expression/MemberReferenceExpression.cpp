/*
 * MemberReferenceExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/MemberReferenceExpression.h"

#include "sc_expression/AbstractExpression.h"
#include "sc_analyze/AnalyzedType.h"

#include "variable_access/VariableInstractionHolder.h"

namespace alinous {

MemberReferenceExpression::MemberReferenceExpression() : AbstractBinaryExpression(CodeElement::EXP_MEMBER_REF) {
}

MemberReferenceExpression::~MemberReferenceExpression() {
}

void MemberReferenceExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void MemberReferenceExpression::analyzeTypeRef(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyzeTypeRef(actx);
}

void MemberReferenceExpression::analyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	VariableInstractionHolder* holder = getVariableInstractionHolder();


	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* exp = this->list.get(i);
		holder->addExpression(exp, actx);
	}

	holder->analyze(actx, this);
}

int MemberReferenceExpression::binarySize() const {
	int total = sizeof(uint16_t);
	total += AbstractBinaryExpression::binarySize();

	return total;
}

void MemberReferenceExpression::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::EXP_MEMBER_REF);
	AbstractBinaryExpression::toBinary(out);
}

void MemberReferenceExpression::fromBinary(ByteBuffer* in) {
	AbstractBinaryExpression::fromBinary(in);
}

AnalyzedType MemberReferenceExpression::getType(AnalyzeContext* actx) {
	VariableInstractionHolder* holder = getVariableInstractionHolder();
	AnalyzedType* atype = holder->getAnalyzedType();

	// analyze member ref type
	return *atype;
}

AbstractVmInstance* MemberReferenceExpression::interpret(VirtualMachine* vm) {
	VariableInstractionHolder* holder = getVariableInstractionHolder();

	return holder->interpret(vm);
}

} /* namespace alinous */
