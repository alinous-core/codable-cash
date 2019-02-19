/*
 * SQLAndExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLANDEXPRESSION_H_
#define SQL_EXPRESSION_SQLANDEXPRESSION_H_

#include "sql_expression/AbstractSQLBinaryExpression.h"

namespace alinous {

class SQLAndExpression : public AbstractSQLBinaryExpression {
public:
	SQLAndExpression();
	virtual ~SQLAndExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLANDEXPRESSION_H_ */
