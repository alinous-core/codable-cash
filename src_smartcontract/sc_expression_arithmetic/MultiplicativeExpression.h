/*
 * MultiplicativeExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_
#define SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {

class MultiplicativeExpression : public AbstractBinaryExpression {
public:
	MultiplicativeExpression();
	virtual ~MultiplicativeExpression();
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_ */
