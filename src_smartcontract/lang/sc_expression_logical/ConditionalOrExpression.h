/*
 * ConditionalOrExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_LOGICAL_CONDITIONALOREXPRESSION_H_
#define SC_EXPRESSION_LOGICAL_CONDITIONALOREXPRESSION_H_

#include "lang/sc_expression/AbstractBinaryExpression.h"

namespace alinous {

class ConditionalOrExpression : public AbstractBinaryExpression {
public:
	ConditionalOrExpression();
	virtual ~ConditionalOrExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_LOGICAL_CONDITIONALOREXPRESSION_H_ */
