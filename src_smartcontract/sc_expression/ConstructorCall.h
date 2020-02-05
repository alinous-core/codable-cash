/*
 * ConstructorCall.h
 *
 *  Created on: 2020/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_CONSTRUCTORCALL_H_
#define SC_EXPRESSION_CONSTRUCTORCALL_H_

#include "sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class ConstructorCall : public AbstractExpression {
public:
	ConstructorCall();
	virtual ~ConstructorCall();

	void setName(AbstractExpression* exp) noexcept;
	void addArgument(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	AbstractExpression* name;
	ArrayList<AbstractExpression> args;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_CONSTRUCTORCALL_H_ */
