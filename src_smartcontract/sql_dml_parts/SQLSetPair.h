/*
 * SQLSetPair.h
 *
 *  Created on: 2019/02/22
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLSETPAIR_H_
#define SQL_DML_PARTS_SQLSETPAIR_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {

class SQLColumnIdentifier;
class AbstractSQLExpression;

class SQLSetPair : public AbstractSQLPart {
public:
	SQLSetPair();
	virtual ~SQLSetPair();

	void setColumn(SQLColumnIdentifier* colId) noexcept;
	void setExpression(AbstractSQLExpression* exp) noexcept;

private:
	SQLColumnIdentifier* colId;
	AbstractSQLExpression* exp;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLSETPAIR_H_ */
