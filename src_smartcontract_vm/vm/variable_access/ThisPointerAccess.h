/*
 * ThisPointerAccess.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_THISPOINTERACCESS_H_
#define VARIABLE_ACCESS_THISPOINTERACCESS_H_

#include "vm/variable_access/AbstractVariableInstraction.h"

namespace alinous {

class AnalyzedType;

class ThisPointerAccess: public AbstractVariableInstraction {
public:
	ThisPointerAccess();
	virtual ~ThisPointerAccess();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element);
	virtual AnalyzedType getAnalyzedType() const noexcept;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst);

	virtual CodeElement* getCodeElement() const noexcept;
private:
	AnalyzedType* atype;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_THISPOINTERACCESS_H_ */
