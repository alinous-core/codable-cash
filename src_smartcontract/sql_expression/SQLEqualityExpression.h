/*
 * SQLEqualityExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLEQUALITYEXPRESSION_H_
#define SQL_EXPRESSION_SQLEQUALITYEXPRESSION_H_

#include "sql_expression/AbstractSQLBinaryExpression.h"

namespace alinous {

class SQLEqualityExpression : public AbstractSQLBinaryExpression {
public:
	SQLEqualityExpression();
	virtual ~SQLEqualityExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLEQUALITYEXPRESSION_H_ */
