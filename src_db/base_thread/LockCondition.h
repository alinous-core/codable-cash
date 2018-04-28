/*
 * LockCondition.h
 *
 *  Created on: 2018/04/28
 *      Author: iizuka
 */

#ifndef BASE_THREAD_LOCKCONDITION_H_
#define BASE_THREAD_LOCKCONDITION_H_

#include <pthread.h>

namespace alinous {

class LockCondition {
public:
	friend class SynchronizedLock;

	LockCondition();
	virtual ~LockCondition();

private:
	pthread_cond_t cond;
};

} /* namespace alinous */

#endif /* BASE_THREAD_LOCKCONDITION_H_ */
