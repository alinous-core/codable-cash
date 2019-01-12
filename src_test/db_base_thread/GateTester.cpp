/*
 * GateTester.cpp
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#include "db_base_thread/GateTester.h"

#include "base_thread/SysThread.h"

namespace alinous {

GateTester::GateTester() {
	this->mode = 0;
	this->startLock = nullptr;
	this->loops = 0;
	this->gate = nullptr;
	this->id = 0;
}

GateTester::~GateTester() {
}

void GateTester::init(int mode, SynchronizedLock* startLock, int loops,	ConcurrentGate* gate) {
	this->mode = mode;
	this->startLock = startLock;
	this->loops = loops;
	this->gate = gate;
}

void GateTester::process() noexcept {
	THREAD_ID id = Os::getCurrentThreadId();
}

} /* namespace alinous */
