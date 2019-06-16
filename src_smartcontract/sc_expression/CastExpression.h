/*
 * CastExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_CASTEXPRESSION_H_
#define SC_EXPRESSION_CASTEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {
class AbstractType;

class CastExpression : public AbstractExpression {
public:
	CastExpression();
	virtual ~CastExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeType(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setType(AbstractType* type) noexcept;
	void setExpression(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType();
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
private:
	AbstractType* type;
	AbstractExpression* exp;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_CASTEXPRESSION_H_ */
