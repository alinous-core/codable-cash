/*
 * VMemPrimitiveList.h
 *
 *  Created on: 2020/03/18
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMPRIMITIVELIST_H_
#define INSTANCE_PARTS_VMEMPRIMITIVELIST_H_

#include "vm/memory/VmMemoryManager.h"
#include "vm/VirtualMachine.h"
#include "instance/instance_parts/VmMalloc.h"


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
		root = (T*)vm->getAlloc()->mallocPtrArray(this->currentSize * sizeof(T));
		this->vm = vm;
	}

	~VMemPrimitiveList() noexcept {
		this->vm->getAlloc()->releaseArray(this->root);
	}

	void addElement(const T value) noexcept {
		if(__builtin_expect(!(this->currentSize > this->numArray), 0)){
			int size = this->currentSize * 2;

			T* newPtr = (T*)vm->getAlloc()->mallocPtrArray(size * sizeof(T)); //new T[size];
			//__memset(newPtr, 0, sizeof(T) * size);

			Mem::memcpy(newPtr, this->root, sizeof(T) * this->currentSize);

			this->vm->getAlloc()->releaseArray(this->root);
			this->root = newPtr;

			this->currentSize = size;
		}

		this->root[this->numArray++] = value;
	}

	inline T get(const int i) const noexcept {
		return *(this->root + i);
	}
	inline int size() const noexcept {
		return numArray;
	}
	void backLast(){
		this->numArray--;
	}

public:
	T* root;
private:
	int numArray;
	int currentSize;
	VirtualMachine* vm;
};

}

#endif /* INSTANCE_PARTS_VMEMPRIMITIVELIST_H_ */
