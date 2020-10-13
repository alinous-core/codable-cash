/*
 * PreIncrementExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARITHMETIC_PREINCREMENTEXPRESSION_H_
#define SC_EXPRESSION_ARITHMETIC_PREINCREMENTEXPRESSION_H_

#include "lang/sc_expression_arithmetic/AbstractArithmeticExpression.h"


namespace alinous {

class PreIncrementExpression : public AbstractArithmeticExpression {
public:
	static int constexpr const PLUS{1};
	static int constexpr const MINUS{2};

	PreIncrementExpression();
	virtual ~PreIncrementExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setOpe(int ope) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	AbstractVmInstance* interpret8Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret16Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret32Bit(VirtualMachine* vm);
	AbstractVmInstance* interpret64Bit(VirtualMachine* vm);
private:
	int ope;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARITHMETIC_PREINCREMENTEXPRESSION_H_ */
