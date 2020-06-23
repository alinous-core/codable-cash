/*
 * VMemHashMapKeySet.h
 *
 *  Created on: 2020/06/22
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_
#define INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_
#include "vm/VirtualMachine.h"
#include <cstddef>

namespace alinous {

template <typename T, typename V>
class VMemHashMapRawArray;
template <typename T, typename V>
class VMemHashMapInternalElement;

template <typename K, typename V>
class VMemHashMapKeySet {
public:
	VMemHashMapKeySet(const VMemHashMapKeySet& inst) = delete;
	VMemHashMapKeySet(VirtualMachine* vm){
		this->list = new(vm) VMemHashMapRawArray<K, V>(vm);
		this->nullElement = nullptr;
	}
	virtual ~VMemHashMapKeySet(){

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

private:
	VMemHashMapRawArray<K, V>* list;
	VMemHashMapInternalElement<K, V>* nullElement;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAPKEYSET_H_ */
