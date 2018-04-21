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

class AbstractThreadRunner {
public:
	AbstractThreadRunner();
	virtual ~AbstractThreadRunner();

	void start() noexcept;
protected:
	static void* threadStartFunction(void* param) noexcept;

	virtual void process() noexcept = 0;
protected:
	SysThread* pThread;
};

} /* namespace alinous */

#endif /* BASE_THREAD_ABSTRACTTHREADRUNNER_H_ */
