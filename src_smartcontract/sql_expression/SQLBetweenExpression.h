/*
 * SQLBetweenExpression.h
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLBETWEENEXPRESSION_H_
#define SQL_EXPRESSION_SQLBETWEENEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLBetweenExpression : public AbstractSQLExpression {
public:
	SQLBetweenExpression();
	virtual ~SQLBetweenExpression();

	void setLeft(AbstractSQLExpression* exp) noexcept;
	void setStart(AbstractSQLExpression* exp) noexcept;
	void setEnd(AbstractSQLExpression* exp) noexcept;

private:
	AbstractSQLExpression* left;
	AbstractSQLExpression* start;
	AbstractSQLExpression* end;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLBETWEENEXPRESSION_H_ */
