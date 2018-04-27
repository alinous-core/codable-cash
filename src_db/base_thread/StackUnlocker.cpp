/*
 * StackUnlocker.cpp
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#include "base_thread/StackUnlocker.h"
#include "base_thread/SysMutex.h"

namespace alinous {

StackUnlocker::StackUnlocker(SysMutex* mutex) : mutex(mutex) {
	mutex->lock();
}

StackUnlocker::~StackUnlocker() {
	mutex->unlock();
}

} /* namespace alinous */
