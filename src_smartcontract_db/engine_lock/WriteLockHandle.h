/*
 * WriteLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_WRITELOCKHANDLE_H_
#define ENGINE_LOCK_WRITELOCKHANDLE_H_

#include "engine_lock/AbstractLockHandle.h"

namespace codablecash {

class WriteLockHandle : public AbstractLockHandle {
public:
	WriteLockHandle(const CdbOid* threadId, AbstractDatabaseLock* lock);
	virtual ~WriteLockHandle();

	virtual bool isWriteLock() const noexcept;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_WRITELOCKHANDLE_H_ */
