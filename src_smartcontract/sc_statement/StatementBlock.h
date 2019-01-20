/*
 * StatementBlock.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_STATEMENTBLOCK_H_
#define SC_STATEMENT_STATEMENTBLOCK_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class StatementBlock : public AbstractStatement {
public:
	StatementBlock();
	virtual ~StatementBlock();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_STATEMENTBLOCK_H_ */
