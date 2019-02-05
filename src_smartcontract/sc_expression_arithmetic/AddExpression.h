/*
 * AddExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ADDEXPRESSION_H_
#define SC_EXPRESSION_ADDEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {

class AddExpression: public AbstractExpression {
public:
	AddExpression();
	virtual ~AddExpression();
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ADDEXPRESSION_H_ */
