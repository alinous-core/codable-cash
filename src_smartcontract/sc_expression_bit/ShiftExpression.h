/*
 * ShiftExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_BIT_SHIFTEXPRESSION_H_
#define SC_EXPRESSION_BIT_SHIFTEXPRESSION_H_
#include <cstdint>

#include "base/RawArrayPrimitive.h"
#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {

class ShiftExpression : public AbstractBinaryExpression {
public:
	static const constexpr uint8_t LEFT{1};
	static const constexpr uint8_t RIGHT{2};

	ShiftExpression();
	virtual ~ShiftExpression();

	void addOpe(uint8_t ope) noexcept;
private:
	RawArrayPrimitive<uint8_t> operations;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_BIT_SHIFTEXPRESSION_H_ */
