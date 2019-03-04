/*
 * DeleteStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_DELETESTATEMENT_H_
#define SQL_DML_DELETESTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {
class SQLFrom;
class SQLWhere;

class DeleteStatement : public AbstractSQLStatement {
public:
	DeleteStatement();
	virtual ~DeleteStatement();

	void setFrom(SQLFrom* from) noexcept;
	void setWhere(SQLWhere* where) noexcept;
private:
	SQLFrom* from;
	SQLWhere* where;
};

} /* namespace alinous */

#endif /* SQL_DML_DELETESTATEMENT_H_ */
