/*
 * VMemPrimitiveList.h
 *
 *  Created on: 2020/03/18
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMPRIMITIVELIST_H_
#define INSTANCE_PARTS_VMEMPRIMITIVELIST_H_

#include "memory/VmMemoryManager.h"
#include "vm/VirtualMachine.h"
#include "instance_parts/VmMalloc.h"


namespace alinous {

template <typename T>
class VMemPrimitiveList {
public:
	void* operator new(size_t size, VirtualMachine* vm){
		VmMemoryManager* mem = vm->getMemory();
		uint64_t mallocSize = size + sizeof(VirtualMachine*);

		void* p = mem->malloc(mallocSize);
		VirtualMachine** vmp = (VirtualMachine**)p;
		*vmp = vm;

		return ((char*)p) + sizeof(VirtualMachine*);
	}

	void operator delete(void* p, size_t size) {
		void* ptr = ((char*)p) - sizeof(VirtualMachine*);

		VirtualMachine** vm = (VirtualMachine**)ptr;
		VmMemoryManager* mem = (*vm)->getMemory();

		mem->free((char*)ptr);
	}

	explicit VMemPrimitiveList(VirtualMachine* vm, int defaultSize) noexcept : numArray(0),
			currentSize(defaultSize > 4 ? defaultSize : 4) {
		root = vm->getAlloc()->mallocPtrArray(this->currentSize * sizeof(T));
		this->vm = vm;
	}

	~VMemPrimitiveList() noexcept {
		this->vm->getAlloc()->releaseArray(this->root);
	}

private:
	int numArray;
	int currentSize;
	T* root;
	VirtualMachine* vm;
};

}

#endif /* INSTANCE_PARTS_VMEMPRIMITIVELIST_H_ */
