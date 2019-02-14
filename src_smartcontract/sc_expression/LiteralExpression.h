/*
 * LiteralExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_LITERALEXPRESSION_H_
#define SC_EXPRESSION_LITERALEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {
class UnicodeString;

class LiteralExpression: public AbstractExpression {
public:
	LiteralExpression();
	virtual ~LiteralExpression();

	void setString(UnicodeString* str, bool dquote) noexcept;

private:
	UnicodeString* str;
	bool dquote;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_LITERALEXPRESSION_H_ */
