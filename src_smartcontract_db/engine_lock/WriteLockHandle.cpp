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
	this->ref--;
	if(this->ref == 0){
		this->lock->writeUnlock(this);
	}
}

} /* namespace codablecash */
