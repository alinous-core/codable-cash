/*
 * ThrowStatement.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_THROWSTATEMENT_H_
#define SC_STATEMENT_CTRL_THROWSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class ThrowStatement : public AbstractStatement {
public:
	ThrowStatement();
	virtual ~ThrowStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_THROWSTATEMENT_H_ */
