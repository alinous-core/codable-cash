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

#include "vm/memory/VmMemoryManager.h"

namespace alinous {

template <typename K, typename V>
class VMemHashmap {
public:
	VMemHashmap(const VMemHashmap& base) = delete;
	explicit VMemHashmap(VirtualMachine* vm){
		this->hashMapKeySet = new(vm) VMemHashMapKeySet<K, V>(vm);
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

	void clear() {
		this->hashMapKeySet->clear();
	}

	V* put(const K* key, V* value) noexcept {
		return this->hashMapKeySet->addElement(key, value);
	}
	V* put(const K& key, V* value) noexcept {
		return this->hashMapKeySet->addElement(&key, value);
	}

	V* get(const K* key) const noexcept {
		return this->hashMapKeySet->getValue(key);
	}
	V* get(const K& key) const noexcept {
		return this->hashMapKeySet->getValue(&key);
	}
	void remove(K* key) {
		this->hashMapKeySet->remove(key);
	}

	VMemHashMapKeySet<K, V>* keySet() const noexcept {
		return this->hashMapKeySet;
	}

	int size() const noexcept {
		return this->hashMapKeySet->size();
	}

	bool isEmpty() const noexcept {
		return size() == 0;
	}
protected:
	VMemHashMapKeySet<K, V>* hashMapKeySet;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMHASHMAP_H_ */
