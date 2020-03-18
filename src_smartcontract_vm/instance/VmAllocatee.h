/*
 * VmAllocatee.h
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#ifndef INSTANCE_VMALLOCATEE_H_
#define INSTANCE_VMALLOCATEE_H_
#include <cstddef>

namespace alinous {

class VirtualMachine;

class VmAllocatee {
public:
	VmAllocatee();
	virtual ~VmAllocatee();

	void* operator new(size_t size, VirtualMachine* vm);
	void operator delete(void* p, size_t size);
};

} /* namespace alinous */

#endif /* INSTANCE_VMALLOCATEE_H_ */
