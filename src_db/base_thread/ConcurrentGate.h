/*
 * ConcurrentGate.h
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#ifndef BASE_THREAD_CONCURRENTGATE_H_
#define BASE_THREAD_CONCURRENTGATE_H_

#include "base_thread/SysMutex.h"
#include "base_thread/SynchronizedLock.h"

namespace alinous {

class ConcurrentGate {
public:
	ConcurrentGate() noexcept;
	virtual ~ConcurrentGate();

	void enter() noexcept;
	void exit() noexcept;
	void open() noexcept;
	void close() noexcept;

private:
	bool isOpened;
	int counter;
	int roomWaiter;

	SysMutex doorKeeperLock;
	SynchronizedLock stateLock;
	SynchronizedLock roomLock;
};

} /* namespace alinous */

#endif /* BASE_THREAD_CONCURRENTGATE_H_ */
