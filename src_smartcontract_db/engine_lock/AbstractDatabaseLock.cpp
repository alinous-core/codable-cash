/*
 * AbstractDatabaseLock.cpp
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#include "engine_lock/AbstractDatabaseLock.h"

#include "base_thread/ConcurrentGate.h"

namespace codablecash {

AbstractDatabaseLock::AbstractDatabaseLock() {
	this->gate = new ConcurrentGate();
}

AbstractDatabaseLock::~AbstractDatabaseLock() {
	delete this->gate;
}

} /* namespace codablecash */
