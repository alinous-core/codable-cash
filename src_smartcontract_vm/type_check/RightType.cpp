/*
 * RightType.cpp
 *
 *  Created on: 2020/02/27
 *      Author: iizuka
 */

#include "type_check/RightType.h"

#include "sc_expression/AbstractExpression.h"


namespace alinous {

RightType::RightType(AbstractExpression* exp) : AbstractTypeCheckTarget(exp) {

}

RightType::~RightType() {

}

} /* namespace alinous */
