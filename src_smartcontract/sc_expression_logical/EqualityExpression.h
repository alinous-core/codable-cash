/*
 * EqualityExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_LOGICAL_EQUALITYEXPRESSION_H_
#define SC_EXPRESSION_LOGICAL_EQUALITYEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"
#include <cstdint>

namespace alinous {

class EqualityExpression : public AbstractExpression {
public:
	static const constexpr uint8_t EQ{1};
	static const constexpr uint8_t NOT_EQ{2};

	EqualityExpression();
	virtual ~EqualityExpression();

	void setLeft(AbstractExpression* exp) noexcept;
	void setRight(AbstractExpression* exp) noexcept;
	void setOp(uint8_t op) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	AbstractExpression* left;
	AbstractExpression* right;
	uint8_t op;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_LOGICAL_EQUALITYEXPRESSION_H_ */
