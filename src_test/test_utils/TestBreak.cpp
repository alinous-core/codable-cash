/*
 * TestBreak.cpp
 *
 *  Created on: 2018/05/01
 *      Author: iizuka
 */

#include "test_utils/TestBreak.h"

#include "base_thread/StackUnlocker.h"


namespace alinous {

TestBreak::TestBreak() : location(0) {

}

TestBreak::~TestBreak() {
}

void TestBreak::resume(int num) {
	this->lock.lock();

	while(location != num){
		this->lock.wait();
	}
	this->lock.notifyAll();

	this->lock.unlock();
}

void TestBreak::breakpoint(int num) {
	StackUnlocker locker(&this->lock);

	this->location = num;
	this->lock.notifyAll();

	this->lock.wait();
}

int TestBreak::current() {
	return this->location;
}

} /* namespace alinous */
