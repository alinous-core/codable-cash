/*
 * AbstractThreadRunner.h
 *
 *  Created on: 2018/04/21
 *      Author: iizuka
 */

#ifndef BASE_THREAD_ABSTRACTTHREADRUNNER_H_
#define BASE_THREAD_ABSTRACTTHREADRUNNER_H_

namespace alinous {

class SysThread;
class UnicodeString;

class AbstractThreadRunner {
public:
	AbstractThreadRunner(const AbstractThreadRunner& inst) = delete;

	AbstractThreadRunner();
	explicit AbstractThreadRunner(const UnicodeString* name);
	virtual ~AbstractThreadRunner();

	void start() noexcept;
	void join() const noexcept;
	SysThread* getThread() const noexcept;
protected:
	static void* threadStartFunction(void* param) noexcept;

	virtual void process() noexcept = 0;
protected:
	SysThread* pThread;
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* BASE_THREAD_ABSTRACTTHREADRUNNER_H_ */
