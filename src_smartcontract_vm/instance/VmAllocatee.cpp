/*
 * VmAllocatee.cpp
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#include "instance/VmAllocatee.h"

#include "vm/VirtualMachine.h"

#include "vm/memory/VmMemoryManager.h"


namespace alinous {

VmAllocatee::VmAllocatee() {
}

VmAllocatee::~VmAllocatee() {

}

void* VmAllocatee::operator new(size_t size, VirtualMachine* vm) {
	VmMemoryManager* mem = vm->getMemory();
	uint64_t mallocSize = size + sizeof(VirtualMachine*);

	void* p = mem->malloc(mallocSize);
	VirtualMachine** vmp = (VirtualMachine**)p;
	*vmp = vm;

	return ((char*)p) + sizeof(VirtualMachine*);
}

void VmAllocatee::operator delete(void* p, size_t size) {
	void* ptr = ((char*)p) - sizeof(VirtualMachine*);

	VirtualMachine** vm = (VirtualMachine**)ptr;
	VmMemoryManager* mem = (*vm)->getMemory();

	mem->free((char*)ptr);
}

} /* namespace alinous */
