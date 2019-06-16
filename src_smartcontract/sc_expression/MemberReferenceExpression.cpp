/*
 * MemberReferenceExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/MemberReferenceExpression.h"

#include "sc_expression/AbstractExpression.h"
#include "sc_analyze/AnalyzedType.h"

namespace alinous {

MemberReferenceExpression::MemberReferenceExpression() : AbstractBinaryExpression(CodeElement::EXP_MEMBER_REF) {
}

MemberReferenceExpression::~MemberReferenceExpression() {
}

void MemberReferenceExpression::preAnalyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::preAnalyze(actx);
}

void MemberReferenceExpression::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME expression : analyze type
}

void MemberReferenceExpression::analyze(AnalyzeContext* actx) {
	AbstractBinaryExpression::analyze(actx);
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

AnalyzedType MemberReferenceExpression::getType() {
	// FIXME analyze member ref type
	return AnalyzedType();
}

AbstractVmInstance* MemberReferenceExpression::interpret(VirtualMachine* vm) {
	return nullptr; // FIXME expression::interpret()
}

} /* namespace alinous */
