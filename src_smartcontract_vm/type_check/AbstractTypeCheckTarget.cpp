/*
 * AbstractTypeCheckTarget.cpp
 *
 *  Created on: 2020/03/02
 *      Author: iizuka
 */

#include "type_check/AbstractTypeCheckTarget.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

AbstractTypeCheckTarget::AbstractTypeCheckTarget(AbstractExpression* exp) {
	this->exp = exp;

}

AbstractTypeCheckTarget::~AbstractTypeCheckTarget() {
	delete this->exp;
}

} /* namespace alinous */
