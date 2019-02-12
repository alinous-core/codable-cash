/*
 * ArrayReferenceExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_
#define SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class ArrayReferenceExpression : public AbstractExpression {
public:
	ArrayReferenceExpression();
	virtual ~ArrayReferenceExpression();

	void setExp(AbstractExpression* exp) noexcept;
	void addIndex(AbstractExpression* exp) noexcept;
private:
	AbstractExpression* exp;
	ArrayList<AbstractExpression> list;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_ */
