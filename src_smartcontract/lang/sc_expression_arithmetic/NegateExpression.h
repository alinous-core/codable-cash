/*
 * NegateExpression.h
 *
 *  Created on: 2019/02/14
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARITHMETIC_NEGATEEXPRESSION_H_
#define SC_EXPRESSION_ARITHMETIC_NEGATEEXPRESSION_H_

#include "lang/sc_expression_arithmetic/AbstractArithmeticExpression.h"

namespace alinous {

class NegateExpression : public AbstractArithmeticExpression {
public:
	NegateExpression();
	virtual ~NegateExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

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
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARITHMETIC_NEGATEEXPRESSION_H_ */
