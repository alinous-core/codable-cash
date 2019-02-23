/*
 * SelectStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_SELECTSTATEMENT_H_
#define SQL_DML_SELECTSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {
class SQLExpressionList;
class SQLFrom;
class SQLWhere;
class SQLLimitOffset;

class SelectStatement : public AbstractSQLStatement {
public:
	SelectStatement();
	virtual ~SelectStatement();

	void setList(SQLExpressionList* list) noexcept;
	void setFrom(SQLFrom* from) noexcept;
	void setWhere(SQLWhere* where) noexcept;
	void setLimitOffset(SQLLimitOffset* limitOffset) noexcept;
private:
	SQLExpressionList* list;
	SQLFrom* from;
	SQLWhere* where;
	SQLLimitOffset* limitOffset;
};

} /* namespace alinous */

#endif /* SQL_DML_SELECTSTATEMENT_H_ */
