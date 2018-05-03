/*
 * StackRelease.h
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#ifndef BASE_STACKRELEASE_H_
#define BASE_STACKRELEASE_H_

#include "ArrayList.h"

namespace alinous {

template <typename T>
class StackRelease {
public:
	explicit StackRelease(T* ptr) : ptr(ptr){
	}
	~StackRelease(){
		if(this->ptr != nullptr){
			delete ptr;
		}
	}
private:
	T* ptr;
};

template <typename T>
class StackArrayRelease {
public:
	explicit StackArrayRelease(T* ptr) : ptr(ptr){
	}
	~StackArrayRelease(){
		if(this->ptr != nullptr){
			delete [] ptr;
		}
	}
private:
	T* ptr;
};

template <typename T>
class StackMultipleRelease {
public:
	StackMultipleRelease(){

	}
	~StackMultipleRelease(){
		int maxLoop = this->ptrlist.size();
		for(int i = 0; i < maxLoop; ++i){
			T* ptr = this->ptrlist.get(i);
			delete ptr;
		}
	}
	void add(T* ptr){
		ptrlist.addElement(ptr);
	}
private:
	ArrayList<T> ptrlist;
};


} /* namespace alinous */

#endif /* BASE_STACKRELEASE_H_ */
