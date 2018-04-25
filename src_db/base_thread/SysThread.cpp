/*
 * SysThread.cpp
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#include "debug/debugMacros.h"

#include "base_thread/SysThread.h"
#include "base/StackRelease.h"



namespace alinous {

SysThread::SysThread(const UnicodeString* name) noexcept : id(0) {
	if(name != nullptr){
		this->name = new UnicodeString(name);
	}else{
		this->name = nullptr;
	}

}

SysThread* SysThread::createThread(const UnicodeString* name, SysThreadRoutine threadFunc, void* params) noexcept {
	assert(threadFunc != nullptr);

	SysThread* thread = new SysThread(name);
	thread->id = Os::createThread(threadFunc, params);

	if(name){
		const char* c_name = name->toCString();
		Os::setThreadName(thread->id, c_name);

		delete [] c_name;
	}

	return thread;
}

SysThread* SysThread::getCurrentThread() noexcept {
	THREAD_ID id = Os::getCurrentThreadId();

	UnicodeString* name = Os::getThreadName(id);
	StackRelease<UnicodeString> r_name(name);

	return new SysThread(name);
}

bool SysThread::equals(const SysThread* other) const noexcept {
	return this->id == other->id;
}

SysThread::~SysThread() {
	if(this->name != nullptr){
		delete this->name;
	}
}

void SysThread::join() const noexcept {
	if(this->id != 0){
		Os::joinThread(this->id);
	}
}

} /* namespace alinous */
