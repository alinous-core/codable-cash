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

class ForStatement: public AbstractStatement {
public:
	ForStatement();
	virtual ~ForStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_FORSTATEMENT_H_ */
