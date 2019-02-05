/*
 * DoWhileStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_DOWHILESTATEMENT_H_
#define SC_STATEMENT_CTRL_DOWHILESTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class DoWhileStatement: public AbstractStatement {
public:
	DoWhileStatement();
	virtual ~DoWhileStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_DOWHILESTATEMENT_H_ */
