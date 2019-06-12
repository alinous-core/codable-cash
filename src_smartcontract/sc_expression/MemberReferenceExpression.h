/*
 * MemberReferenceExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_MEMBERREFERENCEEXPRESSION_H_
#define SC_EXPRESSION_MEMBERREFERENCEEXPRESSION_H_

#include "sc_expression/AbstractBinaryExpression.h"

namespace alinous {
class VariableIdentifier;

class MemberReferenceExpression : public AbstractBinaryExpression {
public:
	MemberReferenceExpression();
	virtual ~MemberReferenceExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType();
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_MEMBERREFERENCEEXPRESSION_H_ */
