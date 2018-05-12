/*
 * LockCondition.cpp
 *
 *  Created on: 2018/04/28
 *      Author: iizuka
 */

#include "base_thread/LockCondition.h"

#include "debug/debugMacros.h"

namespace alinous {

LockCondition::LockCondition() {
	int ret = ::pthread_cond_init(&cond, 0);
	assert(ret == 0);
}

LockCondition::~LockCondition() {
	int ret = ::pthread_cond_destroy(&cond);
	assert(ret == 0);
}

} /* namespace alinous */
