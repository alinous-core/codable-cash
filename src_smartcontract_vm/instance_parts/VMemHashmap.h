/*
 * VMemHashmap.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMHASHMAP_H_
#define INSTANCE_PARTS_VMEMHASHMAP_H_

#include "VMemHashMapRawArray.h"
#include "VMemHashMapKeySet.h"

#include "vm/VirtualMachine.h"

#include "memory/VmMemoryManager.h"

namespace alinous {

template <typename K, typename V>
class VMemHashmap {
public:
	VMemHashmap(const VMemHashmap& base) = delete;
	explicit VMemHashmap(VirtualMachine* vm){
		this->hashMapKeySet = new(vm) VMemHashMapKeySet<K, V>();
	}
	virtual ~VMemHashmap(){
		delete this->hashMapKeySet;
	}

	void* operator new(size_t size, VirtualMachine* vm){
		VmMemoryManager* mem = vm->getMemory();
		uint64_t mallocSize = size + sizeof(VirtualMachine*);

		void* p = mem->malloc(mallocSize);
		VirtualMachine** vmp = (VirtualMachine**)p;
		*vmp = vm;

		return ((char*)p) + sizeof(VirtualMachine*);
	}
	void operator delete(void* p, size_t size){
		void* ptr = ((char*)p) - sizeof(VirtualMachine*);

		VirtualMachine** vm = (VirtualMachine**)ptr;
		VmMemoryManager* mem = (*vm)->getMemory();

		mem->free((char*)ptr);
	}

protected:
	VMemHashMapKeySet<K, V>* hashMapKeySet;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAP_H_ */
