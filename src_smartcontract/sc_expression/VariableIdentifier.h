/*
 * VariableIdentifier.h
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_VARIABLEIDENTIFIER_H_
#define SC_EXPRESSION_VARIABLEIDENTIFIER_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {
class UnicodeString;

class VariableIdentifier: public AbstractExpression {
public:
	VariableIdentifier();
	virtual ~VariableIdentifier();

	void setName(UnicodeString* name) noexcept;
private:
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_VARIABLEIDENTIFIER_H_ */
