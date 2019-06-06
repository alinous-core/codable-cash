/*
 * VmMalloc.h
 *
 *  Created on: 2019/06/05
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMMALLOC_H_
#define INSTANCE_PARTS_VMMALLOC_H_

namespace alinous {

class VirtualMachine;

class VmMalloc {
public:
	explicit VmMalloc(VirtualMachine* vm);
	virtual ~VmMalloc();

	void* mallocPtrArray(int size);
	void releaseArray(void*);

private:
	VirtualMachine* const vm;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMMALLOC_H_ */
