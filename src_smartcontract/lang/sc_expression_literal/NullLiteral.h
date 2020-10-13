/*
 * NullLiteral.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_NULLLITERAL_H_
#define SC_EXPRESSION_NULLLITERAL_H_
#include "lang/sc_expression/AbstractExpression.h"

namespace alinous {

class NullLiteral : public AbstractExpression {
public:
	NullLiteral();
	virtual ~NullLiteral();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_NULLLITERAL_H_ */
