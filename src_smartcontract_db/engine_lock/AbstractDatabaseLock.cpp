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
	ReadLockHandle* handle = this->readHandles.get(&oid);
	if(handle == nullptr){
		this->gate->enter();

		handle = new ReadLockHandle(&oid, this);
		this->readHandles.put(&oid, handle);
	}

	handle->incRef();

	return handle;
}

WriteLockHandle* AbstractDatabaseLock::writeLock() {
	SysThread* thread = SysThread::getCurrentThread();
	uint64_t threadId = (uint64_t)thread->getId();

	CdbOid oid(threadId);
	WriteLockHandle* handle = this->writeHandles.get(&oid);
	if(handle == nullptr){
		this->gate->close();

		handle = new WriteLockHandle(&oid, this);
		this->writeHandles.put(&oid, handle);
	}

	handle->incRef();

	return handle;
}

void AbstractDatabaseLock::readUnlock(const ReadLockHandle* handle) noexcept {

}

void AbstractDatabaseLock::writeUnlock(const WriteLockHandle* handle) noexcept {
}

} /* namespace codablecash */
