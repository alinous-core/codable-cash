/*
 * SQLEqualityExpression.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLEQUALITYEXPRESSION_H_
#define SQL_EXPRESSION_SQLEQUALITYEXPRESSION_H_

#include "sql/AbstractSQLExpression.h"
#include <cstdint>

namespace alinous {

class SQLEqualityExpression : public AbstractSQLExpression {
public:
	static const constexpr uint8_t EQ{1};
	static const constexpr uint8_t NOT_EQ{2};

	SQLEqualityExpression();
	virtual ~SQLEqualityExpression();

	void setLeft(AbstractSQLExpression* exp) noexcept;
	void setRight(AbstractSQLExpression* exp) noexcept;
	void setOp(uint8_t op) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	AbstractSQLExpression* left;
	AbstractSQLExpression* right;
	uint8_t op;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLEQUALITYEXPRESSION_H_ */
