/*
 * ArrayList.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_ARRAYLIST_H_
#define BASE_ARRAYLIST_H_

#include "RawCompare.h"
#include <string.h>

namespace alinous {

#define DEFAULT_RAW_ARRAY_SIZE 64

template <typename T, typename C = RawCompare> class ArrayList {
public:
	typedef T* ElementType;

	ArrayList() throw() : numArray(0), currentSize(DEFAULT_RAW_ARRAY_SIZE),
			root(new ElementType[this->currentSize * sizeof(ElementType)]), cursor(root),
			sorted(false),
			compareFunctor() {
	}

	ArrayList(int defaultSize) throw() : numArray(0), currentSize(defaultSize > 4 ? defaultSize : 4),
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

	void addElement(T* ptr) throw()
	{
		if(__builtin_expect(this->currentSize <= this->numArray, 0)){
			realloc();
		}

		*this->cursor = ptr;

		this->cursor++;
		this->numArray++;
		this->sorted = false;
	}

	void realloc() throw() {
		int lastSize = this->currentSize;
		int size = this->currentSize * 2;

		ElementType* newPtr = new ElementType [size]{};

		const int max = this->currentSize;
		__copy(newPtr, 0, this->root, 0, max);

		this->currentSize = size;

		delete [] this->root;

		this->root = newPtr;
		this->cursor = this->root + this->numArray;
	}

	inline void __copy(T** dest, int dest_start, T** src, int src_start, const int count) throw()
	{
		T** d = dest + dest_start;
		T** s = src + src_start;

		::memcpy(d, s, count * sizeof(T*));
	}

	inline int size() const throw() {
		return numArray;
	}

	inline T* get(int i) const throw() {
		return *(this->root + i);
	}

	inline T* remove(int index) throw()
	{
		T* ptr = get(index);
		remove(index, 1);
		return ptr;
	}

	inline void remove(const int index, const int length) throw()
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
