/*
 * SQLInExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLINEXPRESSION_H_
#define SQL_EXPRESSION_SQLINEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {
class SQLExpressionList;

class SQLInExpression : public AbstractSQLExpression {
public:
	SQLInExpression();
	virtual ~SQLInExpression();

	void setLeft(AbstractSQLExpression* left) noexcept;
	void setList(SQLExpressionList* list) noexcept;
private:
	AbstractSQLExpression* left;
	SQLExpressionList* list;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLINEXPRESSION_H_ */
