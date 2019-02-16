/*
 * SQLColumnIdentifier.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_
#define SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLColumnIdentifier : public AbstractSQLExpression {
public:
	SQLColumnIdentifier();
	virtual ~SQLColumnIdentifier();
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_ */
