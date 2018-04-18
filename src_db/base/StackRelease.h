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
	StackRelease(T* ptr) : ptr(ptr){
	}
	~StackRelease(){
		delete ptr;
	}
private:
	T* ptr;
};

template <typename T>
class StackArrayRelease {
public:
	StackArrayRelease(){

	}
	~StackArrayRelease(){
		int maxLoop = this->ptrlist.size();
		for(int i = 0; i < maxLoop; ++i){
			T* ptr = this->ptrlist.get(i);
			delete ptr;
		}
	}
	void add(T* ptr){
		ptrlist->addElement(ptr);
	}
private:
	ArrayList<T> ptrlist;
};

} /* namespace alinous */

#endif /* BASE_STACKRELEASE_H_ */
