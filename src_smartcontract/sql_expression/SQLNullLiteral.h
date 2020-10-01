/*
 * SQLNullLiteral.h
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLNULLLITERAL_H_
#define SQL_EXPRESSION_SQLNULLLITERAL_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLNullLiteral : public AbstractSQLExpression {
public:
	SQLNullLiteral();
	virtual ~SQLNullLiteral();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLNULLLITERAL_H_ */
