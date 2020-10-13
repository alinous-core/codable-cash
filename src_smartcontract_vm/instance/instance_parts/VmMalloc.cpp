/*
 * VmMalloc.cpp
 *
 *  Created on: 2019/06/05
 *      Author: iizuka
 */

#include <cstdint>

#include "instance/instance_parts/VmMalloc.h"
#include "vm/memory/VmMemoryManager.h"
#include "vm/VirtualMachine.h"

namespace alinous {

VmMalloc::VmMalloc(VirtualMachine* vm) : vm(vm) {

}

VmMalloc::~VmMalloc() {

}

void* VmMalloc::mallocPtrArray(int size) {
	uint64_t mallocSize = size;

	VmMemoryManager* mem = this->vm->getMemory();
	void* p = mem->malloc(mallocSize);

	return p;
}

void VmMalloc::releaseArray(void* ptr) {
	VmMemoryManager* mem = this->vm->getMemory();
	mem->free((char*)ptr);
}

} /* namespace alinous */
