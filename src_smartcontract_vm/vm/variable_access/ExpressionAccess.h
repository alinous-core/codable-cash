/*
 * ExpressionAccess.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_EXPRESSIONACCESS_H_
#define VARIABLE_ACCESS_EXPRESSIONACCESS_H_

#include "vm/variable_access/AbstractVariableInstraction.h"

namespace alinous {

class AbstractExpression;

class ExpressionAccess: public AbstractVariableInstraction {
public:
	explicit ExpressionAccess(AbstractExpression* exp);
	virtual ~ExpressionAccess();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);
	virtual AnalyzedType getAnalyzedType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst);

	virtual CodeElement* getCodeElement() const noexcept;
private:
	AbstractExpression* exp;

	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_EXPRESSIONACCESS_H_ */
