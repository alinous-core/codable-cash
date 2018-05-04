/*
 * AbstractThreadRunner.cpp
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base_thread/AbstractThreadRunner.h"
#include "base_thread/SysThread.h"

#include "base/StackRelease.h"

namespace alinous {

AbstractThreadRunner::AbstractThreadRunner() :pThread(nullptr), name(nullptr) {

}

AbstractThreadRunner::AbstractThreadRunner(const UnicodeString* name) : pThread(nullptr){
	this->name = new UnicodeString(name);
}

AbstractThreadRunner::~AbstractThreadRunner() {
	if(this->pThread){
		delete this->pThread;
	}
	if(this->name){
		delete this->name;
	}
}

void AbstractThreadRunner::start() noexcept {
	this->pThread = SysThread::createThread(this->name, AbstractThreadRunner::threadStartFunction, this);
}

void* AbstractThreadRunner::threadStartFunction(void* param) noexcept {
	AbstractThreadRunner* __this = static_cast<AbstractThreadRunner*>(param);
	__this->process();

	return nullptr;
}

SysThread* AbstractThreadRunner::getThread() const noexcept {
	return this->pThread;
}

void AbstractThreadRunner::join() const noexcept {
	if(this->pThread){
		this->pThread->join();
	}
}

} /* namespace alinous */
