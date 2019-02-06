/*
 * IfStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_IFSTATEMENT_H_
#define SC_STATEMENT_CTRL_IFSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class AbstractExpression;

class IfStatement: public AbstractStatement {
public:
	IfStatement();
	virtual ~IfStatement();

	void setExpression(AbstractExpression* exp) noexcept;
	void setStatement(AbstractStatement* stmt) noexcept;

private:
	AbstractExpression* exp;
	AbstractStatement* stmt;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_IFSTATEMENT_H_ */
