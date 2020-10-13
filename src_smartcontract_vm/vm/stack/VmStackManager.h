/*
 * VmStackManager.h
 *
 *  Created on: 2019/06/30
 *      Author: iizuka
 */

#ifndef STACK_VMSTACKMANAGER_H_
#define STACK_VMSTACKMANAGER_H_

#include "base/ArrayList.h"

namespace alinous {

class VmStack;

class VmStackManager {
public:
	VmStackManager();
	virtual ~VmStackManager();

	void addStack(VmStack* stack) noexcept;
	void popStack() noexcept;
	VmStack* top() const noexcept;
	bool isEmpty() const noexcept;
	int size() const noexcept;
	VmStack* get(int pos) const noexcept;

private:
	ArrayList<VmStack> list;
};

} /* namespace alinous */

#endif /* STACK_VMSTACKMANAGER_H_ */
