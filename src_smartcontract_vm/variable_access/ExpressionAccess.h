/*
 * ExpressionAccess.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_EXPRESSIONACCESS_H_
#define VARIABLE_ACCESS_EXPRESSIONACCESS_H_

#include "variable_access/AbstractVariableInstraction.h"

namespace alinous {

class AbstractExpression;

class ExpressionAccess: public AbstractVariableInstraction {
public:
	ExpressionAccess(AbstractExpression* exp);
	virtual ~ExpressionAccess();

private:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_EXPRESSIONACCESS_H_ */
