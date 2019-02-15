/*
 * ForStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_FORSTATEMENT_H_
#define SC_STATEMENT_CTRL_FORSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {
class AbstractExpression;

class ForStatement: public AbstractStatement {
public:
	ForStatement();
	virtual ~ForStatement();

	void setStatement(AbstractStatement* stmt) noexcept;

	void setInit(AbstractStatement* init) noexcept;
	void setCondition(AbstractExpression* cond) noexcept;
	void setPostLoop(AbstractExpression* postLoop) noexcept;
private:
	AbstractStatement* init;
	AbstractExpression* cond;
	AbstractExpression* postLoop;
	AbstractStatement* stmt;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_FORSTATEMENT_H_ */
