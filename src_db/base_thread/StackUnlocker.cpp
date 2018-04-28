/*
 * StackUnlocker.cpp
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#include "base_thread/StackUnlocker.h"
#include "base_thread/ILock.h"

namespace alinous {

StackUnlocker::StackUnlocker(ILock* mutex) : mutex(mutex) {
	mutex->lock();
}

StackUnlocker::~StackUnlocker() {
	mutex->unlock();
}

} /* namespace alinous */
