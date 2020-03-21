/*
 * FunctionArguments.h
 *
 *  Created on: 2019/11/03
 *      Author: iizuka
 */

#ifndef VARIABLE_ACCESS_FUNCTIONARGUMENTS_H_
#define VARIABLE_ACCESS_FUNCTIONARGUMENTS_H_

#include "base/ArrayList.h"


namespace alinous {

class AbstractVmInstanceSubstance;
class AbstractVmInstance;
class VmClassInstance;

class FunctionArguments {
public:
	FunctionArguments();
	virtual ~FunctionArguments();

	void addSubstance(AbstractVmInstanceSubstance* ref) noexcept;

	void setThisPtr(VmClassInstance* _this) noexcept;
	VmClassInstance* getThisPtr() const noexcept;

	const ArrayList<AbstractVmInstanceSubstance>* getArguments() const noexcept;
	AbstractVmInstance* getReturnedValue() const noexcept;
	void setReturnedValue(AbstractVmInstance* inst) noexcept;

private:
	ArrayList<AbstractVmInstanceSubstance> list;
	AbstractVmInstance* returnedValue;
	VmClassInstance* _this;
};

} /* namespace alinous */

#endif /* VARIABLE_ACCESS_FUNCTIONARGUMENTS_H_ */
