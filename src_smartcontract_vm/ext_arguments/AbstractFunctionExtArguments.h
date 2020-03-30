/*
 * AbstractFunctionExtArguments.h
 *
 *  Created on: 2019/11/17
 *      Author: iizuka
 */

#ifndef EXT_ARGUMENTS_ABSTRACTFUNCTIONEXTARGUMENTS_H_
#define EXT_ARGUMENTS_ABSTRACTFUNCTIONEXTARGUMENTS_H_

namespace alinous {

class AnalyzedType;
class AbstractVmInstance;
class VirtualMachine;
class AbstractReference;
class IAbstractVmInstanceSubstance;

class AbstractFunctionExtArguments {
public:
	AbstractFunctionExtArguments();
	virtual ~AbstractFunctionExtArguments();

	virtual AnalyzedType getType() const noexcept = 0;
	virtual AbstractVmInstance* interpret(VirtualMachine* vm) = 0;
};

} /* namespace alinous */

#endif /* EXT_ARGUMENTS_ABSTRACTFUNCTIONEXTARGUMENTS_H_ */
