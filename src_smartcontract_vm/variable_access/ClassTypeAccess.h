/*
 * ClassTypeAccess.h
 *
 *  Created on: 2020/04/28
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_CLASSTYPEACCESS_H_
#define VARIABLE_ACCESS_CLASSTYPEACCESS_H_

#include "variable_access/AbstractVariableInstraction.h"

namespace alinous {

class ClassTypeAccess : public AbstractVariableInstraction {
public:
	explicit ClassTypeAccess(const AnalyzedType* atype);
	virtual ~ClassTypeAccess();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);
	virtual AnalyzedType getAnalyzedType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst);

	virtual CodeElement* getCodeElement() const noexcept;

private:
	CodeElement* element;
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_CLASSTYPEACCESS_H_ */
