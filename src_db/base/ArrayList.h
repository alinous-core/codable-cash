/*
 * ArrayList.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_ARRAYLIST_H_
#define BASE_ARRAYLIST_H_

#include "RawCompare.h"

namespace alinous {

#define DEFAULT_RAW_ARRAY_SIZE 64

template <typename T, typename C = RawCompare> class RawArray {
public:
	typedef T* ElementType;

	RawArray() throw() : numArray(0), currentSize(DEFAULT_RAW_ARRAY_SIZE),
			root(new ElementType[this->currentSize * sizeof(ElementType)]), cursor(root),
			sorted(false),
			compareFunctor() {
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
