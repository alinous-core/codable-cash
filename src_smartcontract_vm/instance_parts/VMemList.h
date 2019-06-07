/*
 * VMemList.h
 *
 *  Created on: 2019/06/06
 *      Author: iizuka
 */

#ifndef INSTANCE_PARTS_VMEMLIST_H_
#define INSTANCE_PARTS_VMEMLIST_H_

#include "debug/debugMacros.h"
#include "base/RawCompare.h"
#include "osenv/memory.h"

#include "instance_parts/VmMalloc.h"

namespace alinous {

#define DEFAULT_VMMEM_ARRAY_SIZE 64

template <typename T, typename C = RawCompare>
class VMemList {
public:
	typedef T* ElementType;

	VMemList(const VMemList& list) = delete;

	VMemList(VirtualMachine* vm) : numArray(0), currentSize(DEFAULT_RAW_ARRAY_SIZE),
			//root(new ElementType[this->currentSize * sizeof(ElementType)]), cursor(root),
			sorted(false),
			compareFunctor() {
		this->root = (ElementType*)vm->getAlloc()->mallocPtrArray(this->currentSize * sizeof(ElementType));
		this->cursor = this->root;
		this->vm = vm;
	}

	virtual ~VMemList(){
		this->vm->getAlloc()->releaseArray(this->root);
	}

	ElementType* getRoot() const noexcept {
		return this->root;
	}

	void reset() noexcept {
		this->numArray = 0;
		this->cursor = this->root;

		this->sorted = true;
	}


private:
	int numArray;
	int currentSize;
	ElementType* root;
	ElementType* cursor;
	bool sorted;
	const C compareFunctor;

	VirtualMachine* vm;
};

} /* namespace alinous */

#endif /* INSTANCE_PARTS_VMEMLIST_H_ */
