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
class SQLSelectTargetList;
class SQLFrom;
class SQLWhere;
class SQLGroupBy;
class SQLOrderBy;
class SQLLimitOffset;

class SelectStatement : public AbstractSQLStatement {
public:
	SelectStatement();
	virtual ~SelectStatement();

	void setList(SQLSelectTargetList* list) noexcept;
	void setFrom(SQLFrom* from) noexcept;
	void setWhere(SQLWhere* where) noexcept;
	void setGroupBy(SQLGroupBy* groupBy) noexcept;
	void setOrderBy(SQLOrderBy* orderBy) noexcept;
	void setLimitOffset(SQLLimitOffset* limitOffset) noexcept;
private:
	SQLSelectTargetList* list;
	SQLFrom* from;
	SQLWhere* where;
	SQLGroupBy* groupBy;
	SQLOrderBy* orderBy;
	SQLLimitOffset* limitOffset;
};

} /* namespace alinous */

#endif /* SQL_DML_SELECTSTATEMENT_H_ */
