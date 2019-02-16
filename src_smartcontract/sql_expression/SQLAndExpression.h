/*
 * SQLAndExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLANDEXPRESSION_H_
#define SQL_EXPRESSION_SQLANDEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLAndExpression  : public AbstractSQLExpression {
public:
	SQLAndExpression();
	virtual ~SQLAndExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLANDEXPRESSION_H_ */
