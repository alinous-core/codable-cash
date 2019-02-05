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

class IfStatement: public AbstractStatement {
public:
	IfStatement();
	virtual ~IfStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_IFSTATEMENT_H_ */
