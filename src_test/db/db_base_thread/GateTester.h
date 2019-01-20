/*
 * GateTester.h
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#ifndef DB_BASE_THREAD_GATETESTER_H_
#define DB_BASE_THREAD_GATETESTER_H_

#include "base_thread/AbstractThreadRunner.h"
#include "osenv/funcs.h"
#include "base_thread/SynchronizedLock.h"

namespace alinous {

class ConcurrentGate;
class SynchronizedLock;
class Exception;
class CriticalSectionMarker;

class GateTester : public AbstractThreadRunner {
public:
	static const constexpr int WRITER{1};
	static const constexpr int READER{2};

	static SynchronizedLock* launchComplete;
	static CriticalSectionMarker* criticalMarker;
	static Exception* lastException;

	static SynchronizedLock* getStaticLock() noexcept;
	static CriticalSectionMarker* getMarker() noexcept;

	GateTester();
	virtual ~GateTester();
	void init(int mode, SynchronizedLock* startLock, int loops, ConcurrentGate* gate);

	virtual void process() noexcept;

private:
	void writer();
	void reader();

private:
	ConcurrentGate* gate;
	SynchronizedLock* startLock;
	int mode;
	int loops;

	THREAD_ID id;

public:
	bool ready;
};

} /* namespace alinous */

#endif /* DB_BASE_THREAD_GATETESTER_H_ */
