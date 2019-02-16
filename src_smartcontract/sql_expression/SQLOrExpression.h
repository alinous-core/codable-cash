/*
 * SQLOrExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLOREXPRESSION_H_
#define SQL_EXPRESSION_SQLOREXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLOrExpression : public AbstractSQLExpression {
public:
	SQLOrExpression();
	virtual ~SQLOrExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLOREXPRESSION_H_ */
