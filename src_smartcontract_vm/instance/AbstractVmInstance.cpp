/*
 * AbstractVmInstance.cpp
 *
 *  Created on: 2019/05/02
 *      Author: iizuka
 */

#include "instance/AbstractVmInstance.h"

#include "vm/VirtualMachine.h"
#include "memory/VmMemoryManager.h"

namespace alinous {

AbstractVmInstance::AbstractVmInstance(uint8_t type) {
	this->type = type;
}

AbstractVmInstance::~AbstractVmInstance() {
}

void* AbstractVmInstance::operator new(size_t size, VirtualMachine* vm) {
	VmMemoryManager* mem = vm->getMemory();
	uint64_t mallocSize = size + sizeof(VirtualMachine*);

	void* p = mem->malloc(mallocSize);
	VirtualMachine** vmp = (VirtualMachine**)p;
	*vmp = vm;

	return ((char*)p) + sizeof(VirtualMachine*);
}

void AbstractVmInstance::operator delete(void* p, size_t size) {
	void* ptr = ((char*)p) - sizeof(VirtualMachine*);

	VirtualMachine** vm = (VirtualMachine**)ptr;
	VmMemoryManager* mem = (*vm)->getMemory();

	mem->free((char*)ptr);

}

} /* namespace alinous */
