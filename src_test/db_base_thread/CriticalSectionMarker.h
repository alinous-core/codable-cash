/*
 * CriticalSectionMarker.h
 *
 *  Created on: 2019/01/12
 *      Author: iizuka
 */

#ifndef DB_BASE_THREAD_CRITICALSECTIONMARKER_H_
#define DB_BASE_THREAD_CRITICALSECTIONMARKER_H_

#include "base_thread/SynchronizedLock.h"

namespace alinous {

class CriticalSectionMarker {
public:
	CriticalSectionMarker();
	virtual ~CriticalSectionMarker();

	void enter();
	void exit();
	void checkCritical();

private:
	bool critical;
	SynchronizedLock lock;
};

} /* namespace alinous */

#endif /* DB_BASE_THREAD_CRITICALSECTIONMARKER_H_ */
