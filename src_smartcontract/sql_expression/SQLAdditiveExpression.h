/*
 * SQLAdditiveExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_
#define SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_

#include "sql_expression/AbstractSQLBinaryExpression.h"

namespace alinous {

class SQLAdditiveExpression : public AbstractSQLBinaryExpression {
public:
	SQLAdditiveExpression();
	virtual ~SQLAdditiveExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_ */
