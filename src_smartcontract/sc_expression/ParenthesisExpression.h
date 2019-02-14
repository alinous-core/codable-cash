/*
 * ParenthesisExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_PARENTHESISEXPRESSION_H_
#define SC_EXPRESSION_PARENTHESISEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {

class ParenthesisExpression : public AbstractExpression {
public:
	ParenthesisExpression();
	virtual ~ParenthesisExpression();

	void setExp(AbstractExpression* exp) noexcept;

private:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_PARENTHESISEXPRESSION_H_ */
