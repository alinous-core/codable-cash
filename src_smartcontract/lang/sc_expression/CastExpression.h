/*
 * CastExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_CASTEXPRESSION_H_
#define SC_EXPRESSION_CASTEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"

namespace alinous {
class AbstractType;
class PrimitiveReference;
class StackFloatingVariableHandler;

class CastExpression : public AbstractExpression {
public:
	CastExpression();
	virtual ~CastExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setType(AbstractType* type) noexcept;
	void setExpression(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);
	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	AbstractVmInstance* checkArrayType(VirtualMachine* vm, AbstractVmInstance* inst, StackFloatingVariableHandler* releaser);

	AbstractVmInstance* interpretPrimitive(VirtualMachine* vm, PrimitiveReference* p);
private:
	AbstractType* type;
	AbstractExpression* exp;

	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_CASTEXPRESSION_H_ */
