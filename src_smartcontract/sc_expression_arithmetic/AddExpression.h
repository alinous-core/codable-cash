/*
 * AddExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ADDEXPRESSION_H_
#define SC_EXPRESSION_ADDEXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

#include "base/RawArrayPrimitive.h"
#include <cstdint>

namespace alinous {

class AddExpression: public AbstractBinaryExpression {
public:
	static const constexpr uint8_t ADD{1};
	static const constexpr uint8_t SUB{2};

	AddExpression();
	virtual ~AddExpression();

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

#endif /* SC_EXPRESSION_ADDEXPRESSION_H_ */
