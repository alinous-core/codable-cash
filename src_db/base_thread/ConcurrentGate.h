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

class StackReadLock {
public:
	StackReadLock(StackReadLock& inst) = delete;
	StackReadLock(ConcurrentGate* gate) noexcept;
	~StackReadLock();
private:
	ConcurrentGate* gate;
};

class StackWriteLock {
public:
	StackWriteLock(StackWriteLock& inst) = delete;
	StackWriteLock(ConcurrentGate* gate) noexcept;
	~StackWriteLock();
private:
	ConcurrentGate* gate;
};

} /* namespace alinous */

#endif /* BASE_THREAD_CONCURRENTGATE_H_ */
