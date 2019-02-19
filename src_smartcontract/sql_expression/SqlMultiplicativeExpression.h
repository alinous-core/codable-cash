/*
 * SqlMultiplicativeExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLMULTIPLICATIVEEXPRESSION_H_
#define SQL_EXPRESSION_SQLMULTIPLICATIVEEXPRESSION_H_

#include "sql_expression/AbstractSQLBinaryExpression.h"

namespace alinous {

class SqlMultiplicativeExpression : public AbstractSQLBinaryExpression {
public:
	SqlMultiplicativeExpression();
	virtual ~SqlMultiplicativeExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLMULTIPLICATIVEEXPRESSION_H_ */
