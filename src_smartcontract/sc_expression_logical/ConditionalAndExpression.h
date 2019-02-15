/*
 * ConditionalAndExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_LOGICAL_CONDITIONALANDEXPRESSION_H_
#define SC_EXPRESSION_LOGICAL_CONDITIONALANDEXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {

class ConditionalAndExpression : public AbstractBinaryExpression {
public:
	ConditionalAndExpression();
	virtual ~ConditionalAndExpression();
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_LOGICAL_CONDITIONALANDEXPRESSION_H_ */
