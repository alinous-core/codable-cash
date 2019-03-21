/*
 * NotExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_LOGICAL_NOTEXPRESSION_H_
#define SC_EXPRESSION_LOGICAL_NOTEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {

class NotExpression : public AbstractExpression {
public:
	NotExpression();
	virtual ~NotExpression();

	void setExpression(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_LOGICAL_NOTEXPRESSION_H_ */
