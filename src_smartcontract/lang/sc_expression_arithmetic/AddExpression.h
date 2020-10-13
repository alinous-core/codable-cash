/*
 * AddExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ADDEXPRESSION_H_
#define SC_EXPRESSION_ADDEXPRESSION_H_

#include <cstdint>

#include "lang/sc_expression_arithmetic/AbstractArithmeticBinaryExpresson.h"
#include "engine/sc_analyze/AnalyzedType.h"
#include "base/RawArrayPrimitive.h"

namespace alinous {

class AddExpression: public AbstractArithmeticBinaryExpresson {
public:
	static const constexpr uint8_t ADD{1};
	static const constexpr uint8_t SUB{2};

	AddExpression();
	virtual ~AddExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	AbstractVmInstance* interpret8Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret16Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret32Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret64Bit(VirtualMachine* vm);

};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ADDEXPRESSION_H_ */
