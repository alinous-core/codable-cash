/*
 * SQLAdditiveExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_
#define SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLAdditiveExpression : public AbstractSQLExpression {
public:
	SQLAdditiveExpression();
	virtual ~SQLAdditiveExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLADDITIVEEXPRESSION_H_ */
