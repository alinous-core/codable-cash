/*
 * AbstractBinaryExpression.h
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ABSTRACTBINARYEXPRESSION_H_
#define SC_EXPRESSION_ABSTRACTBINARYEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class AbstractBinaryExpression : public AbstractExpression {
public:
	explicit AbstractBinaryExpression(int kind);
	virtual ~AbstractBinaryExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void init(VirtualMachine* vm);

	void addExp(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
protected:
	ArrayList<AbstractExpression> list;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ABSTRACTBINARYEXPRESSION_H_ */
