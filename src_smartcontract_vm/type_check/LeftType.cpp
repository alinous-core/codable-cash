/*
 * LeftType.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "type_check/LeftType.h"

#include "sc_expression/AbstractExpression.h"

namespace alinous {

LeftType::LeftType(AbstractExpression* exp) : AbstractTypeCheckTarget(exp) {

}

LeftType::~LeftType() {

}

int LeftType::checkTypeCompatibility(AnalyzeContext* actx, RightType* rightType) {

}

} /* namespace alinous */
