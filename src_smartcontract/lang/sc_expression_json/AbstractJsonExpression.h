/*
 * AbstractJsonExpression.h
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_JSON_ABSTRACTJSONEXPRESSION_H_
#define SC_EXPRESSION_JSON_ABSTRACTJSONEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"

namespace alinous {

class AbstractJsonExpression : public AbstractExpression {
public:
	explicit AbstractJsonExpression(int kind);
	virtual ~AbstractJsonExpression();
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_JSON_ABSTRACTJSONEXPRESSION_H_ */
