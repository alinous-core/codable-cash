/*
 * ReadLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_READLOCKHANDLE_H_
#define ENGINE_LOCK_READLOCKHANDLE_H_

#include "engine_lock/AbstractLockHandle.h"

namespace codablecash {

class ReadLockHandle : public AbstractLockHandle {
public:
	ReadLockHandle(const CdbOid* threadId, AbstractDatabaseLock* lock);
	virtual ~ReadLockHandle();

	virtual bool isWriteLock() const noexcept;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_READLOCKHANDLE_H_ */
