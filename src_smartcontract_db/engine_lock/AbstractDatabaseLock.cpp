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
#include "base_thread/SysMutex.h"

#include "base/StackRelease.h"

#include "base_thread/StackUnlocker.h"
using namespace alinous;

namespace codablecash {

AbstractDatabaseLock::AbstractDatabaseLock() {
	this->gate = new ConcurrentGate();
	this->hashMutex = new SysMutex();
}

AbstractDatabaseLock::~AbstractDatabaseLock() {
	delete this->gate;
	delete this->hashMutex;
}

ReadLockHandle* AbstractDatabaseLock::readLock() {
	SysThread* thread = SysThread::getCurrentThread(); __STP(thread);
	uint64_t threadId = (uint64_t)thread->getId();

	CdbOid oid(threadId);

	ReadLockHandle* handle = nullptr;
	{
		StackUnlocker stackLock(this->hashMutex);

		handle = this->readHandles.get(&oid);

		if(handle == nullptr){
			this->gate->enter();

			handle = new ReadLockHandle(&oid, this);

			this->readHandles.put(&oid, handle);
		}

		handle->incRef();// ref for times the thread locked
	}

	return handle;
}

WriteLockHandle* AbstractDatabaseLock::writeLock() {
	SysThread* thread = SysThread::getCurrentThread(); __STP(thread);
	uint64_t threadId = (uint64_t)thread->getId();

	CdbOid oid(threadId);
	WriteLockHandle* handle = nullptr;
	{
		StackUnlocker stackLock(this->hashMutex);

		handle = this->writeHandles.get(&oid);

		if(handle == nullptr){
			this->gate->close();

			handle = new WriteLockHandle(&oid, this);

			this->writeHandles.put(&oid, handle);
		}

		handle->incRef(); // ref for times the thread locked
	}

	return handle;
}

void AbstractDatabaseLock::unclockHandle(AbstractLockHandle* handle) noexcept {
	handle->decRef();

	if(handle->isReleasable()){
		if(handle->isWriteLock()){
			WriteLockHandle* wh = dynamic_cast<WriteLockHandle*>(handle);
			assert(wh != nullptr);

			writeUnlock(wh);
		}
		else{
			ReadLockHandle* rh = dynamic_cast<ReadLockHandle*>(handle);
			assert(rh != nullptr);

			readUnlock(rh);
		}
	}
}

void AbstractDatabaseLock::readUnlock(ReadLockHandle* handle) noexcept {
	{
		StackUnlocker stackLock(this->hashMutex);

		const CdbOid* key = handle->getThreadId();
		this->readHandles.remove(key);
		delete handle;

		this->gate->exit();
	}
}


void AbstractDatabaseLock::writeUnlock(WriteLockHandle* handle) noexcept {
	{
		StackUnlocker stackLock(this->hashMutex);

		const CdbOid* key = handle->getThreadId();
		this->writeHandles.remove(key);
		delete handle;

		this->gate->open();
	}
}

} /* namespace codablecash */
