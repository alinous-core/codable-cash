/*
 * TryStatement.h
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_CTRL_TRYSTATEMENT_H_
#define SC_STATEMENT_CTRL_TRYSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class TryStatement : public AbstractStatement {
public:
	TryStatement();
	virtual ~TryStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_CTRL_TRYSTATEMENT_H_ */
