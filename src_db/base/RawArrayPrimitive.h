/*
 * RawArrayPrimitive.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_RAWARRAYPRIMITIVE_H_
#define BASE_RAWARRAYPRIMITIVE_H_

#include <string.h>


namespace alinous {

template <typename T>
class RawArrayPrimitive {
public:
	RawArrayPrimitive(int defaultSize) noexcept : numArray(0),
			currentSize(defaultSize > 4 ? defaultSize : 4),
			root(new T[currentSize]),
			sorted(false){
	}

	~RawArrayPrimitive() noexcept {
		delete [] root;
	}


	void addElement(const T value) noexcept {
		if(__builtin_expect(this->currentSize == this->numArray, 0)){
			int size = this->currentSize * 2;

			T* newPtr =new T[size];
			//__memset(newPtr, 0, sizeof(T) * size);

			::memcpy(newPtr, this->root, sizeof(T) * this->currentSize);

			delete [] this->root;
			this->root = newPtr;

			this->currentSize = size;
		}

		this->root[this->numArray++] = value;

		this->sorted = false;
	}

	inline int size() const noexcept {
		return numArray;
	}
	inline T get(const int i) const noexcept {
		return *(this->root + i);
	}
	/*inline T* getPtr(const int i) const noexcept {
		return (this->root + i);
	}
	*/
	inline void set(const int i, T value) const noexcept {
		*(this->root + i) = value;
	}

	inline void setNumArray(int numArray) noexcept {
		this->numArray = numArray;
	}
private:
	int numArray;
	int currentSize;
	T* root;
	bool sorted;
};

}

#endif /* BASE_RAWARRAYPRIMITIVE_H_ */
