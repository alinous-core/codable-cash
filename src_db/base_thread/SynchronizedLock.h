/*
 * SynchronizedLock.h
 *
 *  Created on: 2018/04/28
 *      Author: iizuka
 */

#ifndef BASE_THREAD_SYNCHRONIZEDLOCK_H_
#define BASE_THREAD_SYNCHRONIZEDLOCK_H_

#include <pthread.h>

#include "base_thread/ILock.h"
#include "base_thread/LockCondition.h"

namespace alinous {

class SynchronizedLock : public ILock {
public:
	SynchronizedLock();
	virtual ~SynchronizedLock();

	virtual void lock();
	virtual void unlock();
	void wait();
	void notifyAll();


protected:
	LockCondition* cond;
	pthread_mutex_t mutex;
};

} /* namespace alinous */

#endif /* BASE_THREAD_SYNCHRONIZEDLOCK_H_ */
