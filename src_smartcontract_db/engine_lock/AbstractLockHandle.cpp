/*
 * AbstractLockHandle.cpp
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#include "engine_lock/AbstractLockHandle.h"
#include "engine_lock/AbstractDatabaseLock.h"

#include "engine/CdbOid.h"


namespace codablecash {

AbstractLockHandle::AbstractLockHandle(const CdbOid* threadId, AbstractDatabaseLock* lock) {
	this->threadId = new CdbOid(*threadId);
	this->lock = lock;
	this->ref = 0;
}

AbstractLockHandle::~AbstractLockHandle() {
	delete this->threadId;
	this->lock = nullptr;
}

void AbstractLockHandle::incRef() noexcept {
	this->ref++;
}

void AbstractLockHandle::decRef() noexcept {
	this->ref--;
}

bool AbstractLockHandle::isReleasable() {
	return this->ref <= 0;
}



} /* namespace codablecash */
