/*
 * SysMutex.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_SYSMUTEX_H_
#define BASE_SYSMUTEX_H_

#include <pthread.h>

#include "base_thread/ILock.h"

namespace alinous {

class SysMutex : public ILock {
public:
	SysMutex() noexcept;
	virtual ~SysMutex() noexcept;

	virtual void lock() noexcept;
	virtual void unlock() noexcept;
private:
	pthread_mutex_t mutex;
	int count;
};

} /* namespace codablecash */

#endif /* BASE_SYSMUTEX_H_ */
