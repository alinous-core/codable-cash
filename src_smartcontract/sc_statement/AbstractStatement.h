/*
 * AbstractStatement.h
 *
 *  Created on: 2019/01/20
 *      Author: iizuka
 */

#ifndef SC_STATEMENT_ABSTRACTSTATEMENT_H_
#define SC_STATEMENT_ABSTRACTSTATEMENT_H_

#include "sc/CodeElement.h"

namespace alinous {

class AbstractStatement : public CodeElement {
public:
	explicit AbstractStatement(short kind);
	virtual ~AbstractStatement();
};

} /* namespace alinous */

#endif /* SC_STATEMENT_ABSTRACTSTATEMENT_H_ */
