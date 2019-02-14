/*
 * NullLiteral.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_NULLLITERAL_H_
#define SC_EXPRESSION_NULLLITERAL_H_
#include "sc_expression/AbstractExpression.h"

namespace alinous {

class NullLiteral : public AbstractExpression {
public:
	NullLiteral();
	virtual ~NullLiteral();
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_NULLLITERAL_H_ */
