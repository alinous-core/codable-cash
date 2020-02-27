/*
 * AbstractVariableInstraction.h
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_
#define VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_

namespace alinous {

class AnalyzeContext;
class AnalyzedType;
class AbstractVmInstance;
class VirtualMachine;
class CodeElement;

class AbstractVariableInstraction {
public:
	AbstractVariableInstraction();
	virtual ~AbstractVariableInstraction();

	virtual void analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) = 0;
	virtual AnalyzedType getAnalyzedType() const noexcept = 0;
	virtual bool hasErrorOnAnalyze() const noexcept;

	virtual CodeElement* getCodeElement() const noexcept = 0;

	virtual AbstractVmInstance* interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) = 0;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_ABSTRACTVARIABLEINSTRACTION_H_ */
