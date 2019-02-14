/*
 * AddExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ADDEXPRESSION_H_
#define SC_EXPRESSION_ADDEXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {

class AddExpression: public AbstractBinaryExpression {
public:
	AddExpression();
	virtual ~AddExpression();
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ADDEXPRESSION_H_ */
