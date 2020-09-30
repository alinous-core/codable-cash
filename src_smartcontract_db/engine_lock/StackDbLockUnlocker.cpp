/*
 * StackDbLockUnlocker.cpp
 *
 *  Created on: 2020/09/30
 *      Author: iizuka
 */

#include "engine_lock/StackDbLockUnlocker.h"
#include "engine_lock/AbstractDatabaseLock.h"
#include "engine_lock/AbstractLockHandle.h"

namespace codablecash {

StackDbLockUnlocker::StackDbLockUnlocker(AbstractLockHandle* handle) {
	this->handle =handle;
}

StackDbLockUnlocker::~StackDbLockUnlocker() {
	AbstractDatabaseLock* lock = this->handle->getLock();

	lock->unclockHandle(this->handle); // handle is deleted if necessary
	this->handle = nullptr;
}

} /* namespace codablecash */
