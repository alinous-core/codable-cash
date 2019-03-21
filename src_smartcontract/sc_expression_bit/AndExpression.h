/*
 * AndExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_BIT_ANDEXPRESSION_H_
#define SC_EXPRESSION_BIT_ANDEXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {

class AndExpression : public AbstractBinaryExpression {
public:
	AndExpression();
	virtual ~AndExpression();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_BIT_ANDEXPRESSION_H_ */
