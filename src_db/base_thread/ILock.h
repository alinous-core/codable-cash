/*
 * ILock.h
 *
 *  Created on: 2018/04/28
 *      Author: iizuka
 */

#ifndef BASE_THREAD_ILOCK_H_
#define BASE_THREAD_ILOCK_H_

namespace alinous {

class ILock {
public:
	virtual ~ILock() noexcept;
	virtual void lock() = 0;
	virtual void unlock() = 0;
};

} /* namespace alinous */

#endif /* BASE_THREAD_ILOCK_H_ */
