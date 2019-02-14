/*
 * ReturnStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_RETURNSTATEMENT_H_
#define SC_STATEMENT_CTRL_RETURNSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class ReturnStatement: public AbstractStatement {
public:
	ReturnStatement();
	virtual ~ReturnStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_RETURNSTATEMENT_H_ */
