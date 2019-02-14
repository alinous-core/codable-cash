/*
 * AbstractBinaryExpression.h
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ABSTRACTBINARYEXPRESSION_H_
#define SC_EXPRESSION_ABSTRACTBINARYEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class AbstractBinaryExpression : public AbstractExpression {
public:
	explicit AbstractBinaryExpression(int kind);
	virtual ~AbstractBinaryExpression();

	void addExp(AbstractExpression* exp) noexcept;

protected:
	ArrayList<AbstractExpression> list;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ABSTRACTBINARYEXPRESSION_H_ */
