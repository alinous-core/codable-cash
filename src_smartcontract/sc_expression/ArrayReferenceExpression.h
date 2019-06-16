/*
 * ArrayReferenceExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_
#define SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class ArrayReferenceExpression : public AbstractExpression {
public:
	ArrayReferenceExpression();
	virtual ~ArrayReferenceExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeType(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setExp(AbstractExpression* exp) noexcept;
	void addIndex(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType();
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
private:
	AbstractExpression* exp;
	ArrayList<AbstractExpression> list;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_ */
