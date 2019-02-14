/*
 * ExclusiveOrExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_BIT_EXCLUSIVEOREXPRESSION_H_
#define SC_EXPRESSION_BIT_EXCLUSIVEOREXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {

class ExclusiveOrExpression : public AbstractBinaryExpression {
public:
	ExclusiveOrExpression();
	virtual ~ExclusiveOrExpression();
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_BIT_EXCLUSIVEOREXPRESSION_H_ */
