/*
 * VariableDeclareStatement.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_VARIABLEDECLARESTATEMENT_H_
#define SC_STATEMENT_VARIABLEDECLARESTATEMENT_H_

#include "sc_statement/AbstractStatement.h"

namespace alinous {

class VariableDeclareStatement: public AbstractStatement {
public:
	VariableDeclareStatement();
	virtual ~VariableDeclareStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_VARIABLEDECLARESTATEMENT_H_ */
