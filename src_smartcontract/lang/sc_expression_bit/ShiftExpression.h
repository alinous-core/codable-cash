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
#include "lang/sc_expression_arithmetic/AbstractArithmeticBinaryExpresson.h"


namespace alinous {

class ShiftExpression : public AbstractArithmeticBinaryExpresson {
public:
	static const constexpr uint8_t LEFT{1};
	static const constexpr uint8_t RIGHT{2};

	ShiftExpression();
	virtual ~ShiftExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void addOpe(uint8_t ope) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	AbstractVmInstance* interpret8Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret16Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret32Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret64Bit(VirtualMachine* vm);

private:
	RawArrayPrimitive<uint8_t> operations;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_BIT_SHIFTEXPRESSION_H_ */
