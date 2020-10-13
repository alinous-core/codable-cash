/*
 * MultiplicativeExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_
#define SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_

#include <cstdint>

#include "lang/sc_expression_arithmetic/AbstractArithmeticBinaryExpresson.h"

#include "base/RawArrayPrimitive.h"
#include "engine/sc_analyze/AnalyzedType.h"


namespace alinous {

class MultiplicativeExpression : public AbstractArithmeticBinaryExpresson {
public:
	static const constexpr uint8_t MUL{1};
	static const constexpr uint8_t DIV{2};
	static const constexpr uint8_t MOD{3};

	MultiplicativeExpression();
	virtual ~MultiplicativeExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	AbstractVmInstance* interpret8Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret16Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret32Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret64Bit(VirtualMachine* vm);

	void checkZeroDiv(int64_t val, VirtualMachine* vm) const;

};

} /* namespace alinous */

#endif /* SC_EXPRESSION_MULTIPLICATIVEEXPRESSION_H_ */
