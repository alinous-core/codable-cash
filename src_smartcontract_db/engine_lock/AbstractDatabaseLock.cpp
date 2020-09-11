/*
 * AbstractDatabaseLock.cpp
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#include "engine_lock/AbstractDatabaseLock.h"
#include "engine_lock/ReadLock.h"
#include "engine_lock/WriteLock.h"

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

ReadLock* AbstractDatabaseLock::readLock() {
	SysThread* thread = SysThread::getCurrentThread();
}

WriteLock* AbstractDatabaseLock::writeLock() {
}

} /* namespace codablecash */
