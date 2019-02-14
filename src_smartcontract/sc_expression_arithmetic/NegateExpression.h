/*
 * NegateExpression.h
 *
 *  Created on: 2019/02/14
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARITHMETIC_NEGATEEXPRESSION_H_
#define SC_EXPRESSION_ARITHMETIC_NEGATEEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {

class NegateExpression : public AbstractExpression {
public:
	NegateExpression();
	virtual ~NegateExpression();

	void setExpression(AbstractExpression* exp) noexcept;
private:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARITHMETIC_NEGATEEXPRESSION_H_ */
