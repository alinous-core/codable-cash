/*
 * AbstractLockHandle.cpp
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#include "engine_lock/AbstractLockHandle.h"

#include "engine/CdbOid.h"

namespace codablecash {

AbstractLockHandle::AbstractLockHandle(const CdbOid* threadId) {
	this->threadId = new CdbOid(*threadId);
}

AbstractLockHandle::~AbstractLockHandle() {
	delete this->threadId;
}

} /* namespace codablecash */
