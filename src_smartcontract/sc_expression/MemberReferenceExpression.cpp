/*
 * MemberReferenceExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/MemberReferenceExpression.h"

#include "sc_expression/AbstractExpression.h"

namespace alinous {

MemberReferenceExpression::MemberReferenceExpression() : AbstractBinaryExpression(CodeElement::EXP_MEMBER_REF) {
}

MemberReferenceExpression::~MemberReferenceExpression() {
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

} /* namespace alinous */
