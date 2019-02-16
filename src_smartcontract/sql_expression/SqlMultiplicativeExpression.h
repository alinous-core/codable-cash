/*
 * SqlMultiplicativeExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLMULTIPLICATIVEEXPRESSION_H_
#define SQL_EXPRESSION_SQLMULTIPLICATIVEEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SqlMultiplicativeExpression : public AbstractSQLExpression {
public:
	SqlMultiplicativeExpression();
	virtual ~SqlMultiplicativeExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLMULTIPLICATIVEEXPRESSION_H_ */
