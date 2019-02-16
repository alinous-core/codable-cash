/*
 * SQLRelationalExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLRELATIONALEXPRESSION_H_
#define SQL_EXPRESSION_SQLRELATIONALEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLRelationalExpression : public AbstractSQLExpression {
public:
	SQLRelationalExpression();
	virtual ~SQLRelationalExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLRELATIONALEXPRESSION_H_ */
