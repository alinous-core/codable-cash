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

class SQLLikeExpression : public AbstractSQLExpression {
public:
	SQLLikeExpression();
	virtual ~SQLLikeExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLLIKEEXPRESSION_H_ */
