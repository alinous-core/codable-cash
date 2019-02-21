/*
 * InsertStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_INSERTSTATEMENT_H_
#define SQL_DML_INSERTSTATEMENT_H_

#include "sql/AbstractSQLStatement.h"

namespace alinous {
class TableIdentifier;
class SQLColumnsList;
class SQLExpressionList;

class InsertStatement : public AbstractSQLStatement {
public:
	InsertStatement();
	virtual ~InsertStatement();

	void setTable(TableIdentifier* tableId) noexcept;
	void setColumns(SQLColumnsList* columns) noexcept;
	void setExpressionList(SQLExpressionList* expList) noexcept;
private:
	TableIdentifier* tableId;
	SQLColumnsList* columns;
	SQLExpressionList* expList;
};

} /* namespace alinous */

#endif /* SQL_DML_INSERTSTATEMENT_H_ */
