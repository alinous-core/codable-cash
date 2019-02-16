/*
 * AbstractSQLStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_ABSTRACTSQLSTATEMENT_H_
#define SQL_ABSTRACTSQLSTATEMENT_H_

#include "sc_statement/AbstractStatement.h"
#include "sql/ISQLElement.h"

namespace alinous {

class AbstractSQLStatement : public AbstractStatement, public ISQLElement {
public:
	explicit AbstractSQLStatement(int kind);
	virtual ~AbstractSQLStatement();
};

} /* namespace alinous */

#endif /* SQL_ABSTRACTSQLSTATEMENT_H_ */
