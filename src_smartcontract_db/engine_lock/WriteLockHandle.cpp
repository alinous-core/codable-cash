/*
 * WriteLock.cpp
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#include "engine_lock/WriteLockHandle.h"

#include "engine_lock/AbstractDatabaseLock.h"

namespace codablecash {

WriteLockHandle::WriteLockHandle(const CdbOid* threadId, AbstractDatabaseLock* lock) : AbstractLockHandle(threadId, lock) {

}

WriteLockHandle::~WriteLockHandle() {

}

bool WriteLockHandle::isWriteLock() const noexcept {
	return true;
}

} /* namespace codablecash */
