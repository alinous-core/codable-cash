/*
 * AbstractDatabaseLock.cpp
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#include "engine_lock/AbstractDatabaseLock.h"
#include "engine_lock/ReadLockHandle.h"
#include "engine_lock/WriteLockHandle.h"

#include "engine/CdbOid.h"

#include "base_thread/ConcurrentGate.h"
#include "base_thread/SysThread.h"


using namespace alinous;

namespace codablecash {

AbstractDatabaseLock::AbstractDatabaseLock() {
	this->gate = new ConcurrentGate();
}

AbstractDatabaseLock::~AbstractDatabaseLock() {
	delete this->gate;
}

ReadLockHandle* AbstractDatabaseLock::readLock() {
	SysThread* thread = SysThread::getCurrentThread();
	uint64_t threadId = (uint64_t)thread->getId();

	CdbOid oid(threadId);


}

WriteLockHandle* AbstractDatabaseLock::writeLock() {
}

} /* namespace codablecash */
