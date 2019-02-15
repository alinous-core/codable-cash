/*
 * OrExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_BIT_OREXPRESSION_H_
#define SC_EXPRESSION_BIT_OREXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {

class OrExpression : public AbstractBinaryExpression {
public:
	OrExpression();
	virtual ~OrExpression();
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_BIT_OREXPRESSION_H_ */
