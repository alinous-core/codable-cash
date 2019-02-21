/*
 * SQLWhere.h
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLWHERE_H_
#define SQL_DML_PARTS_SQLWHERE_H_

#include "sql/AbstractSQLPart.h"

namespace alinous {

class AbstractSQLExpression;

class SQLWhere : public AbstractSQLPart {
public:
	SQLWhere();
	virtual ~SQLWhere();

	void setExpression(AbstractSQLExpression* exp) noexcept;
private:
	AbstractSQLExpression* exp;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLWHERE_H_ */
