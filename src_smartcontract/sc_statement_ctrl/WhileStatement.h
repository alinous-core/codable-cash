/*
 * WhileStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_WHILESTATEMENT_H_
#define SC_STATEMENT_CTRL_WHILESTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class WhileStatement: public AbstractStatement {
public:
	WhileStatement();
	virtual ~WhileStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_WHILESTATEMENT_H_ */
