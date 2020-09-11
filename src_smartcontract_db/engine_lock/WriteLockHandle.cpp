/*
 * WriteLock.cpp
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#include "engine_lock/WriteLockHandle.h"

namespace codablecash {

WriteLockHandle::WriteLockHandle(const CdbOid* threadId, AbstractDatabaseLock* lock) : AbstractLockHandle(threadId, lock) {

}

WriteLockHandle::~WriteLockHandle() {

}

} /* namespace codablecash */
