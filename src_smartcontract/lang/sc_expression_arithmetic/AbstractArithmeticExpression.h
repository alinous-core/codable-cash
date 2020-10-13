/*
 * AbstractArithmeticExpression.h
 *
 *  Created on: 2020/03/07
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICEXPRESSION_H_
#define SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"

namespace alinous {

class AbstractArithmeticExpression : public AbstractExpression {
public:
	AbstractArithmeticExpression(int kind);
	virtual ~AbstractArithmeticExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setExpression(AbstractExpression* exp) noexcept;
protected:
	AbstractExpression* exp;
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ARITHMETIC_ABSTRACTARITHMETICEXPRESSION_H_ */
