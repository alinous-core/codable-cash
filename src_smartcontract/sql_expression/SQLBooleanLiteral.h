/*
 * SQLBooleanLiteral.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLBOOLEANLITERAL_H_
#define SQL_EXPRESSION_SQLBOOLEANLITERAL_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLBooleanLiteral : public AbstractSQLExpression {
public:
	SQLBooleanLiteral();
	virtual ~SQLBooleanLiteral();

	void setValue(bool value) noexcept;
private:
	bool value;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLBOOLEANLITERAL_H_ */
