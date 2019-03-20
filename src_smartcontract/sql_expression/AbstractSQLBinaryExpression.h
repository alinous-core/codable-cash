/*
 * AbstractSQLBinaryExpression.h
 *
 *  Created on: 2019/02/20
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_ABSTRACTSQLBINARYEXPRESSION_H_
#define SQL_EXPRESSION_ABSTRACTSQLBINARYEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class AbstractSQLBinaryExpression : public AbstractSQLExpression {
public:
	explicit AbstractSQLBinaryExpression(int kind);
	virtual ~AbstractSQLBinaryExpression();

	void addOperand(AbstractSQLExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
protected:
	ArrayList<AbstractSQLExpression> operands;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_ABSTRACTSQLBINARYEXPRESSION_H_ */
