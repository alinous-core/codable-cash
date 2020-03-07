/*
 * AbstractArithmeticExpression.h
 *
 *  Created on: 2020/03/07
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICEXPRESSION_H_
#define SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {

class AbstractArithmeticExpression : public AbstractExpression {
public:
	AbstractArithmeticExpression(int kind);
	virtual ~AbstractArithmeticExpression();

	void setExpression(AbstractExpression* exp) noexcept;
protected:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICEXPRESSION_H_ */
