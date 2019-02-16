/*
 * SQLInExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLINEXPRESSION_H_
#define SQL_EXPRESSION_SQLINEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLInExpression : public AbstractSQLExpression {
public:
	SQLInExpression();
	virtual ~SQLInExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLINEXPRESSION_H_ */
