/*
 * VariableIdentifier.h
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_VARIABLEIDENTIFIER_H_
#define SC_EXPRESSION_VARIABLEIDENTIFIER_H_

#include "sc_expression/AbstractExpression.h"

namespace alinous {
class UnicodeString;
class AbstractVariableInstraction;

class VariableIdentifier: public AbstractExpression {
public:
	static const UnicodeString __THIS;

	VariableIdentifier();
	virtual ~VariableIdentifier();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setName(UnicodeString* name) noexcept;
	const UnicodeString* getName() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

	bool isThis() const noexcept;
private:
	UnicodeString* name;

	bool executable;
	AbstractVariableInstraction* access;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_VARIABLEIDENTIFIER_H_ */
