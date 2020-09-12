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
	SysThread* thread = SysThread::getCurrentThread();
	uint64_t threadId = (uint64_t)thread->getId();

	CdbOid oid(threadId);

	this->hashMutex->lock();
	ReadLockHandle* handle = this->readHandles.get(&oid);
	this->hashMutex->unlock();

	if(handle == nullptr){
		this->gate->enter();

		handle = new ReadLockHandle(&oid, this);

		this->hashMutex->lock();
		this->readHandles.put(&oid, handle);
		this->hashMutex->unlock();
	}

	handle->incRef();

	return handle;
}

WriteLockHandle* AbstractDatabaseLock::writeLock() {
	SysThread* thread = SysThread::getCurrentThread();
	uint64_t threadId = (uint64_t)thread->getId();

	CdbOid oid(threadId);

	this->hashMutex->lock();
	WriteLockHandle* handle = this->writeHandles.get(&oid);
	this->hashMutex->unlock();

	if(handle == nullptr){
		this->gate->close();

		handle = new WriteLockHandle(&oid, this);

		this->hashMutex->lock();
		this->writeHandles.put(&oid, handle);
		this->hashMutex->unlock();
	}

	handle->incRef();

	return handle;
}

void AbstractDatabaseLock::readUnlock(const ReadLockHandle* handle) noexcept {
	const CdbOid* key = handle->getThreadId();

	this->hashMutex->lock();
	this->readHandles.remove(key);
	this->hashMutex->unlock();
}

void AbstractDatabaseLock::writeUnlock(const WriteLockHandle* handle) noexcept {
	const CdbOid* key = handle->getThreadId();

	this->hashMutex->lock();
	this->writeHandles.remove(key);
	this->hashMutex->unlock();
}

} /* namespace codablecash */
