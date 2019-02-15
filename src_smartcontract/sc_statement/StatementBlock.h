/*
 * StatementBlock.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_STATEMENTBLOCK_H_
#define SC_STATEMENT_STATEMENTBLOCK_H_

#include "sc_statement/AbstractStatement.h"
#include "base/ArrayList.h"

namespace alinous {

class StatementBlock : public AbstractStatement {
public:
	StatementBlock();
	virtual ~StatementBlock();

	void addStatement(AbstractStatement* stmt) noexcept;
private:
	ArrayList<AbstractStatement> statements;
};

} /* namespace alinous */

#endif /* SC_STATEMENT_STATEMENTBLOCK_H_ */
