/*
 * SysThread.cpp
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#include <base_thread/SysThread.h>
#include "base/StackRelease.h"

#include <assert.h>

namespace alinous {

SysThread::SysThread(const UnicodeString* name) noexcept : id(0) {
	if(name != nullptr){
		this->name = new UnicodeString(name);
	}else{
		this->name = nullptr;
	}

}

SysThread* SysThread::createThread(SysThreadRoutine threadFunc, void* params) noexcept {
	return createThread(nullptr, threadFunc, params);
}

SysThread* SysThread::createThread(const UnicodeString* name, SysThreadRoutine threadFunc, void* params) noexcept {
	assert(threadFunc != nullptr);

	SysThread* thread = new SysThread(name);

	::pthread_create( &(thread->id), nullptr, threadFunc, params);

	const char* c_name = name->toCString();
	Os::setThreadName(thread->id, c_name);

	delete [] c_name;

	return thread;
}

SysThread* SysThread::getCurrentThread() noexcept {
	THREAD_ID id = Os::getCurrentThreadId();

	Os::getThreadName(id);

	UnicodeString* name = Os::getThreadName(id);
	StackRelease<UnicodeString> r_name(name);

	return new SysThread(name);
}

SysThread::~SysThread() {
	if(this->name != nullptr){
		delete this->name;
	}
}

} /* namespace alinous */
