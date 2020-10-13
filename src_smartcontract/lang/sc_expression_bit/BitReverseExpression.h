/*
 * BitReverseExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_BIT_BITREVERSEEXPRESSION_H_
#define SC_EXPRESSION_BIT_BITREVERSEEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"

namespace alinous {

class BitReverseExpression : public AbstractExpression {
public:
	BitReverseExpression();
	virtual ~BitReverseExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setExpression(AbstractExpression* exp) noexcept;

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
	AbstractExpression* exp;
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_BIT_BITREVERSEEXPRESSION_H_ */
