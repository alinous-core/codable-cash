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

class ExpressionAccess: public AbstractVariableInstraction {
public:
	ExpressionAccess();
	virtual ~ExpressionAccess();
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_EXPRESSIONACCESS_H_ */
