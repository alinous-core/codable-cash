/*
 * SQLLiteral.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLLITERAL_H_
#define SQL_EXPRESSION_SQLLITERAL_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLLiteral : public AbstractSQLExpression {
public:
	SQLLiteral();
	virtual ~SQLLiteral();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLLITERAL_H_ */
