/*
 * AbstractExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ABSTRACTEXPRESSION_H_
#define SC_EXPRESSION_ABSTRACTEXPRESSION_H_

#include "sc/CodeElement.h"

namespace alinous {

class AnalyzeContext;
class AnalyzedType;
class VirtualMachine;
class AbstractVmInstance;
class VariableInstractionHolder;

class AbstractExpression: public CodeElement {
public:
	explicit AbstractExpression(int kind);
	virtual ~AbstractExpression();

	virtual void preAnalyze(AnalyzeContext* actx) = 0;
	virtual void analyzeTypeRef(AnalyzeContext* actx) = 0;
	virtual void analyze(AnalyzeContext* actx) = 0;
	virtual AnalyzedType getType() = 0;

	virtual void init(VirtualMachine* vm) = 0;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm) = 0;

	VariableInstractionHolder* getVariableInstractionHolder() noexcept;

private:
	VariableInstractionHolder* valInstHolder;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ABSTRACTEXPRESSION_H_ */
