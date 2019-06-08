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

#include "vm/VirtualMachine.h"
namespace alinous {

#define DEFAULT_VMMEM_ARRAY_SIZE 64

template <typename T, typename C = RawCompare>
class VMemList {
public:
	typedef T* ElementType;

	VMemList(const VMemList& list) = delete;

	explicit VMemList(VirtualMachine* vm) : numArray(0), currentSize(DEFAULT_VMMEM_ARRAY_SIZE),
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

	void addElement(T* ptr)
	{
		if(__builtin_expect(this->currentSize <= this->numArray, 0)){
			realloc();
		}

		*this->cursor = ptr;

		this->cursor++;
		this->numArray++;
		this->sorted = false;
	}

	void setElement(T* ptr, int index) noexcept {
		assert(this->numArray > index);

		*(this->root + index) = ptr;
	}

	void realloc() {

		int size = this->currentSize * 2;

		ElementType* newPtr = (ElementType*)this->vm->getAlloc()->mallocPtrArray(size * sizeof(ElementType)); //new ElementType [size]{};

		const int max = this->currentSize;
		__copy(newPtr, 0, this->root, 0, max);

		this->currentSize = size;

		//delete [] this->root;
		this->vm->getAlloc()->releaseArray(this->root);

		this->root = newPtr;
		this->cursor = this->root + this->numArray;
	}

	inline void __copy(T** dest, int dest_start, T** src, int src_start, const int count) noexcept
	{
		T** d = dest + dest_start;
		T** s = src + src_start;

		Mem::memcpy(d, s, count * sizeof(T*));
	}

	inline int size() const noexcept {
		return numArray;
	}

	inline bool isEmpty() const noexcept {
		return numArray == 0;
	}

	inline T* get(int i) const noexcept {
		return *(this->root + i);
	}

	inline int indexOfPtr(const T* ptr){
		int maxLoop = this->size();
		for(int i = 0; i != maxLoop; ++i){
			if(ptr == get(i)){
				return i;
			}
		}

		return -1;
	}

	inline T* remove(int index) noexcept
	{
		T* ptr = get(index);
		remove(index, 1);
		return ptr;
	}

	inline void remove(const int index, const int length) noexcept
	{
#ifdef __DEBUG__
		assert(index + length <= this->numArray);
#endif
		const int copySize = (this->numArray - index - length);
		if(copySize > 0){
			for(int i = 0; i < copySize; i++){
				this->root[index + i] = this->root[index + i + length];
			}
			//__move(this->root, index, this->root, index + length, copySize);
		}

		this->numArray = this->numArray - length;
		this->cursor -= length;
	}

	bool removeByObj(const T* obj) throw()
	{
		int index = indexOfPtr(obj);

		if(index < 0){
			return false;
		}

		remove(index);

		return true;
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
