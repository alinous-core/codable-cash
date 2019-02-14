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

} /* namespace alinous */
