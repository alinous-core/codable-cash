/*
 * AbstractSQLExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_ABSTRACTSQLEXPRESSION_H_
#define SQL_ABSTRACTSQLEXPRESSION_H_

#include "sql/ISQLElement.h"
#include "sc/CodeElement.h"

namespace alinous {

class AbstractSQLExpression: public CodeElement, public ISQLElement {
public:
	AbstractSQLExpression(int kind);
	virtual ~AbstractSQLExpression();

	virtual bool isExecutable();
};

} /* namespace alinous */

#endif /* SQL_ABSTRACTSQLEXPRESSION_H_ */
