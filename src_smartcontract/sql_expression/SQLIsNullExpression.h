/*
 * SQLIsNullExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLISNULLEXPRESSION_H_
#define SQL_EXPRESSION_SQLISNULLEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLIsNullExpression : public AbstractSQLExpression {
public:
	SQLIsNullExpression();
	virtual ~SQLIsNullExpression();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLISNULLEXPRESSION_H_ */
