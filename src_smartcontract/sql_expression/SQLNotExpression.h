/*
 * SQLNotExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLNOTEXPRESSION_H_
#define SQL_EXPRESSION_SQLNOTEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"

namespace alinous {

class SQLNotExpression : public AbstractSQLExpression {
public:
	SQLNotExpression();
	virtual ~SQLNotExpression();

	void setExpression(AbstractSQLExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	AbstractSQLExpression* exp;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLNOTEXPRESSION_H_ */
