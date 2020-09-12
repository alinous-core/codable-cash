/*
 * SysThread.h
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#ifndef BASE_THREAD_SYSTHREAD_H_
#define BASE_THREAD_SYSTHREAD_H_

#include "osenv/funcs.h"
#include "base/UnicodeString.h"

namespace alinous {

class SysThread {
private:
	SysThread(const SysThread& base) = delete;
	explicit SysThread(const UnicodeString* name) noexcept;
public:
	static SysThread* createThread(const UnicodeString* name, SysThreadRoutine threadFunc, void* params) noexcept;
	static SysThread* getCurrentThread() noexcept;
	virtual ~SysThread();

	void join() const noexcept;

	bool equals(const SysThread* other) const noexcept;

	THREAD_ID getId() const noexcept {
		return id;
	}

private:
	THREAD_ID id;
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* BASE_THREAD_SYSTHREAD_H_ */
