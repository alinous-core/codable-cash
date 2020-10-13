/*
 * AbstractSQLStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_ABSTRACTSQLSTATEMENT_H_
#define SQL_ABSTRACTSQLSTATEMENT_H_

#include "lang/sc_statement/AbstractStatement.h"
#include "lang_sql/sql/ISQLElement.h"

namespace alinous {

class AbstractSQLStatement : public AbstractStatement, public ISQLElement {
public:
	explicit AbstractSQLStatement(int kind);
	virtual ~AbstractSQLStatement();

	virtual void init(VirtualMachine* vm);
	virtual bool hasCtrlStatement() const noexcept;
};

} /* namespace alinous */

#endif /* SQL_ABSTRACTSQLSTATEMENT_H_ */
