/*
 * ParenthesisExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_PARENTHESISEXPRESSION_H_
#define SC_EXPRESSION_PARENTHESISEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"

namespace alinous {

class ParenthesisExpression : public AbstractExpression {
public:
	ParenthesisExpression();
	virtual ~ParenthesisExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setExp(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
private:
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_PARENTHESISEXPRESSION_H_ */
