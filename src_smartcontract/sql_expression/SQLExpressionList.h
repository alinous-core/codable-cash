/*
 * SQLExpressionList.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLEXPRESSIONLIST_H_
#define SQL_DML_PARTS_SQLEXPRESSIONLIST_H_

#include "sql/AbstractSQLExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class SQLExpressionList : public AbstractSQLExpression {
public:
	SQLExpressionList();
	virtual ~SQLExpressionList();

	void addExpression(AbstractSQLExpression* exp) noexcept;
private:
	ArrayList<AbstractSQLExpression> list;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLEXPRESSIONLIST_H_ */
