/*
 * ClassTypeAccess.h
 *
 *  Created on: 2020/04/28
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_CLASSTYPEACCESS_H_
#define VARIABLE_ACCESS_CLASSTYPEACCESS_H_

#include "vm/variable_access/AbstractVariableInstraction.h"

namespace alinous {

class VariableIdentifier;

class ClassTypeAccess : public AbstractVariableInstraction {
public:
	explicit ClassTypeAccess(const AnalyzedType* atype);
	explicit ClassTypeAccess(VariableIdentifier* superId);
	virtual ~ClassTypeAccess();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);
	virtual AnalyzedType getAnalyzedType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst);

	virtual CodeElement* getCodeElement() const noexcept;

private:
	void analyzeSuperId(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);

private:
	CodeElement* element;
	AnalyzedType* atype;

	VariableIdentifier* superId;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_CLASSTYPEACCESS_H_ */
