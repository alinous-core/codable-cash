/*
 * StackRelease.h
 *
 *  Created on: 2018/04/15
 *      Author: iizuka
 */

#ifndef BASE_STACKRELEASE_H_
#define BASE_STACKRELEASE_H_

namespace alinous {

template <typename T>
class StackRelease {
public:
	inline StackRelease(T* ptr) : ptr(ptr){
	}
	inline ~StackRelease(){
		delete ptr;
	}
private:
	T* ptr;
};

} /* namespace alinous */

#endif /* BASE_STACKRELEASE_H_ */
