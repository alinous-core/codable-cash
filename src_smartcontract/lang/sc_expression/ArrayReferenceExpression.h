/*
 * ArrayReferenceExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_
#define SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class ArrayReferenceExpression : public AbstractExpression {
public:
	ArrayReferenceExpression();
	virtual ~ArrayReferenceExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setExp(AbstractExpression* exp) noexcept;
	AbstractExpression* getExp() const noexcept;
	void addIndex(AbstractExpression* exp) noexcept;

	int getDim() const noexcept;
	const ArrayList<AbstractExpression>* getIndexList() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	void analyzeDomArray(AnalyzeContext* actx);
	AbstractVmInstance* interpretDomArray(VirtualMachine* vm, AbstractVmInstance* inst);

private:
	AbstractExpression* exp;
	ArrayList<AbstractExpression> list;

	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARRAYREFERENCEEXPRESSION_H_ */
