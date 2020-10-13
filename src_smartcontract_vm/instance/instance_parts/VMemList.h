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

#include "instance/instance_parts/VmMalloc.h"

#include "vm/VirtualMachine.h"
#include "vm/memory/VmMemoryManager.h"

namespace alinous {

#define DEFAULT_VMMEM_ARRAY_SIZE 64

template <typename T, typename C = RawCompare>
class VMemList {
public:
	typedef T* ElementType;

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

	VMemList(const VMemList& list) = delete;

	explicit VMemList(VirtualMachine* vm) : numArray(0), currentSize(DEFAULT_VMMEM_ARRAY_SIZE),
			//root(new ElementType[this->currentSize * sizeof(ElementType)]), cursor(root),
			sorted(false),
			compareFunctor() {
		this->root = (ElementType*)vm->getAlloc()->mallocPtrArray(this->currentSize * sizeof(ElementType));
		this->cursor = this->root;
		this->vm = vm;
	}

	VMemList(VirtualMachine* vm, int defSize) : numArray(0), currentSize(defSize),
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

	void deleteElements(){
		int maxLoop = size();
		for(int i = 0; i != maxLoop; ++i){
			T* ptr = get(i);
			if(ptr != nullptr){
				delete ptr;
			}
		}
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
			T* other = get(i);

			if((compareFunctor)(ptr, other) == 0){
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

	void addElementWithSorted(T* ptr) {
		if(!this->sorted && size() > 1){
			sort();
		}

		int index = indexOfInsert(ptr);

		insertWithKeepingOrder(ptr, index);
	}

	T* search(const T* value) noexcept
	{
		if(this->numArray == 0){
			return 0;
		}

		if(!this->sorted){
			this->sort();
		}
		int begin = 0;
		int end = this->numArray - 1;
		int mid = (begin + end) / 2;

		const ElementType* const _root = this->root;
		while(begin <= end) {
			mid = (begin + end) / 2;

			if(compareFunctor(_root[mid], value) == 0){
				return _root[mid];
			}
			else if((compareFunctor)(_root[mid], value) < 0){ // this->root[mid] < value
				begin = mid + 1;
			}
			else{ // this->root[mid] > value
				end = mid - 1;
			}
		}

		return nullptr;
	}

	void sort() noexcept
	{
		int length = this->numArray;

		int middle = (length) / 2;

		for (int i = middle; i >= 0; i--) {
		    downheap(i, length - 1);
		}

		for (int i = length - 1; i > 0; i--) {
		    swap(0, i);
		    downheap(0, i - 1);
		}
		this->sorted = true;
	}


private:
	int indexOfInsert(const T* value) const noexcept
	{
		if(this->numArray < 4){
			return indexOfInsertByLoop(value);
		}

		int begin = 0;
		int end = this->numArray - 1;
		int mid = (begin + end) / 2;

		const ElementType* const _root = this->root;
		while(begin <= end) {
			mid = (begin + end) / 2;

			int result = compareFunctor(_root[mid], value);
			if(result < 0){
				begin = mid + 1;
			}
			else if(result > 0){
				end = mid - 1;
			}
			else {
				return mid;
			}
		}

		if(end < 0){
			return 0;
		}
		else if(begin >= this->numArray){
			return this->numArray;
		}

		return begin;
	}

	int indexOfInsertByLoop(const T* value) const noexcept
	{
		const ElementType* const _root = this->root;
		int maxLoop = this->numArray;
		for(int i = 0; i != maxLoop; ++i){
			if(compareFunctor(value, _root[i]) <= 0){
				return i;
			}
		}

		return maxLoop;
	}

	void insertWithKeepingOrder(T* ptr, int index)
	{
		if(__builtin_expect(this->currentSize == this->numArray, 0)){
			realloc();
		}

		for(int i = this->numArray; i != index; i--){
			*(this->root + i)= *(this->root + i - 1);
		}


		this->root[index] = ptr;

		this->numArray++;
		this->cursor++;
	}

	void downheap(int rootDefault, int leaf) const throw()
	{
		int root = rootDefault;
		int left = (root + 1) * 2 - 1;;
		int right = left + 1;
		const T* leafMax  = nullptr;
		const T* rootValue = nullptr;
		const ElementType* const _root = this->root;

		while (left <= leaf) {
			if(right <= leaf){ // The tree has right
				left = compareFunctor(_root[left], _root[right]) < 0 ? right : left;
			}

			leafMax = _root[left];
			rootValue = _root[root];

			if(compareFunctor(leafMax, rootValue) < 0){
				return;
			}

			swap(root, left);
			//debugPrint("swap() :");

			// next status
			root = left;
			left = (root + 1) * 2 - 1;
			right = left + 1;
		}
	}
	void swap(const int i, const int j) const throw()
	{
		T* tmp = root[i];
		root[i] = root[j];
		root[j] = tmp;
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
