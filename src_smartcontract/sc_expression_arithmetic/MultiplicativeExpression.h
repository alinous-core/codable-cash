/*
 * MultiplicativeExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_
#define SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

#include "base/RawArrayPrimitive.h"
#include <cstdint>

namespace alinous {

class MultiplicativeExpression : public AbstractBinaryExpression {
public:
	static const constexpr uint8_t MUL{1};
	static const constexpr uint8_t DIV{2};
	static const constexpr uint8_t MOD{3};

	MultiplicativeExpression();
	virtual ~MultiplicativeExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void addOpe(uint8_t ope) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
private:
	RawArrayPrimitive<uint8_t> operations;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_ */
