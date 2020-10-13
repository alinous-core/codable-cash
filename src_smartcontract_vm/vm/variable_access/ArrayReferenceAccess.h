/*
 * ArrayReferenceAccess.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_ARRAYREFERENCEACCESS_H_
#define VARIABLE_ACCESS_ARRAYREFERENCEACCESS_H_

#include "vm/variable_access/AbstractVariableInstraction.h"

namespace alinous {

class ArrayReferenceExpression;

class ArrayReferenceAccess: public AbstractVariableInstraction {
public:
	ArrayReferenceAccess(ArrayReferenceExpression* arrayRefExp);
	virtual ~ArrayReferenceAccess();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);
	virtual AnalyzedType getAnalyzedType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst);

	virtual CodeElement* getCodeElement() const noexcept;

	void setExpressionAccess(AbstractVariableInstraction* expAccess) noexcept;

private:
	void analyzeDimensions(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);

	void analyzeDomArray(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);
	AbstractVmInstance* interpretDomArray(VirtualMachine* vm, AbstractVmInstance* lastInst, AbstractVmInstance* inst);

private:
	ArrayReferenceExpression* arrayRefExp;

	AbstractVariableInstraction* expAccess;
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_ARRAYREFERENCEACCESS_H_ */
