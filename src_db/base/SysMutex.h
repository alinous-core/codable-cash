/*
 * SysMutex.h
 *
 *  Created on: 2018/04/13
 *      Author: iizuka
 */

#ifndef BASE_SYSMUTEX_H_
#define BASE_SYSMUTEX_H_

#include <pthread.h>

namespace codablecash {

class SysMutex {
public:
	SysMutex();
	~SysMutex();

	void lock() throw();
	void unlock() throw();
private:
	pthread_mutex_t mutex;
};

} /* namespace codablecash */

#endif /* BASE_SYSMUTEX_H_ */
