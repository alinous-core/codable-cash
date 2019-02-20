/*
 * SQLLikeExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLLIKEEXPRESSION_H_
#define SQL_EXPRESSION_SQLLIKEEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {
class SQLLiteral;

class SQLLikeExpression : public AbstractSQLExpression {
public:
	SQLLikeExpression();
	virtual ~SQLLikeExpression();

	void setLeft(AbstractSQLExpression* left) noexcept;
	void setRight(SQLLiteral* right) noexcept;
	void setEscape(SQLLiteral* escape) noexcept;
private:
	AbstractSQLExpression* left;
	SQLLiteral* right;
	SQLLiteral* escape;

};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLLIKEEXPRESSION_H_ */
