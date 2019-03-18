/*
 * SQLPlaceHolder.h
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLPLACEHOLDER_H_
#define SQL_EXPRESSION_SQLPLACEHOLDER_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class AbstractExpression;

class SQLPlaceHolder : public AbstractSQLExpression {
public:
	SQLPlaceHolder();
	virtual ~SQLPlaceHolder();

	void setExpression(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLPLACEHOLDER_H_ */
