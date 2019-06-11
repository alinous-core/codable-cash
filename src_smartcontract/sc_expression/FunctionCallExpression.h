/*
 * FunctionCallExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_FUNCTIONCALLEXPRESSION_H_
#define SC_EXPRESSION_FUNCTIONCALLEXPRESSION_H_

#include "sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {
class UnicodeString;

class FunctionCallExpression : public AbstractExpression {
public:
	FunctionCallExpression();
	virtual ~FunctionCallExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setName(AbstractExpression* exp) noexcept;
	void addArgument(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType();
private:
	AbstractExpression* name;
	ArrayList<AbstractExpression> args;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_FUNCTIONCALLEXPRESSION_H_ */
