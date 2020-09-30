/*
 * ReadLock.cpp
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#include "engine_lock/ReadLockHandle.h"
#include "engine_lock/AbstractDatabaseLock.h"

namespace codablecash {

ReadLockHandle::ReadLockHandle(const CdbOid* threadId, AbstractDatabaseLock* lock) : AbstractLockHandle(threadId, lock) {

}

ReadLockHandle::~ReadLockHandle() {

}

bool ReadLockHandle::isWriteLock() const noexcept {
	return false;
}


} /* namespace codablecash */
