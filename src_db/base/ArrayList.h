/*
 * ArrayList.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_ARRAYLIST_H_
#define BASE_ARRAYLIST_H_

#include "RawCompare.h"
#include "osenv/memory.h"

#include "debug/debugMacros.h"

namespace alinous {

#define DEFAULT_RAW_ARRAY_SIZE 64

template <typename T, typename C = RawCompare> class ArrayList {
public:
	typedef T* ElementType;

	ArrayList() noexcept : numArray(0), currentSize(DEFAULT_RAW_ARRAY_SIZE),
			root(new ElementType[this->currentSize * sizeof(ElementType)]), cursor(root),
			sorted(false),
			compareFunctor() {
	}

	ArrayList(const ArrayList& list) = delete;

	explicit ArrayList(int defaultSize) noexcept : numArray(0), currentSize(defaultSize > 4 ? defaultSize : 4),
			root(new ElementType[this->currentSize * sizeof(ElementType)]), cursor(root),
			sorted(false),
			compareFunctor(){
	}

	~ArrayList(){
		if(this->root != nullptr){
			delete [] this->root;
			this->root = nullptr;
		}
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

	void reset() throw() {
		this->numArray = 0;
		this->cursor = this->root;

		this->sorted = true;
	}


	void addAll(ArrayList<T, C>* list){
		int maxLoop = list->size();
		for(int i = 0; i != maxLoop; ++i){
			T* ptr = list->get(i);
			addElement(ptr);
		}
	}

	void addElement(T* ptr) noexcept
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

	void realloc() noexcept {

		int size = this->currentSize * 2;

		ElementType* newPtr = new ElementType [size]{};

		const int max = this->currentSize;
		__copy(newPtr, 0, this->root, 0, max);

		this->currentSize = size;

		delete [] this->root;

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

	void addElementWithSorted(T* ptr) throw() {
		if(!this->sorted && size() > 1){
			sort();
		}

		int index = indexOfInsert(ptr);

		#ifdef __DEBUG__
		if(size() == 0){
			assert(index == 0);
		}
		else if(index < size()){
			const T* last = get(index);
			int diff = compareFunctor(ptr, last, nullptr);
			assert(diff <= 0);
			if(index > 0){
				T* before = get(index - 1);
				diff = compareFunctor(before, ptr, nullptr);
				assert(diff <= 0);
			}
		}else {
			const T* before = get(index - 1);
			int diff = compareFunctor(before, ptr, nullptr);
			assert(diff <= 0);
		}
		#endif

		insertWithKeepingOrder(ptr, index);
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

	void insertWithKeepingOrder(T* ptr, int index) noexcept
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

public:
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
};

}


#endif /* BASE_ARRAYLIST_H_ */
