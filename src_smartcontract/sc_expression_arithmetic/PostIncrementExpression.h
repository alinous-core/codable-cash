/*
 * PostIncrementExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARITHMETIC_POSTINCREMENTEXPRESSION_H_
#define SC_EXPRESSION_ARITHMETIC_POSTINCREMENTEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {

class PostIncrementExpression : public AbstractExpression {
public:
	static int constexpr const PLUS{1};
	static int constexpr const MINUS{2};

	PostIncrementExpression();
	virtual ~PostIncrementExpression();

	void setExpression(AbstractExpression* exp) noexcept;
	void setOpe(int ope) noexcept;
private:
	AbstractExpression* exp;
	int ope;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARITHMETIC_POSTINCREMENTEXPRESSION_H_ */
