/*
 * AbstractThreadRunner.cpp
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#include "base_thread/AbstractThreadRunner.h"
#include "base_thread/SysThread.h"

namespace alinous {

AbstractThreadRunner::AbstractThreadRunner() : pThread(nullptr){

}

AbstractThreadRunner::~AbstractThreadRunner() {
	if(this->pThread){
		delete this->pThread;
	}
}

void AbstractThreadRunner::start() noexcept {
	this->pThread = SysThread::createThread(AbstractThreadRunner::threadStartFunction, this);
}

void* AbstractThreadRunner::threadStartFunction(void* param) noexcept {
	AbstractThreadRunner* __this = (AbstractThreadRunner*)param;
	__this->process();

	return nullptr;
}


} /* namespace alinous */
