/*
 * AbstractDatabaseLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_ABSTRACTDATABASELOCK_H_
#define ENGINE_LOCK_ABSTRACTDATABASELOCK_H_

#include "base/HashMap.h"


namespace alinous {
class ConcurrentGate;
class SysMutex;
}
using namespace alinous;

namespace codablecash {

class CdbOid;
class ReadLockHandle;
class WriteLockHandle;
class AbstractLockHandle;

class AbstractDatabaseLock {
public:
	AbstractDatabaseLock();
	virtual ~AbstractDatabaseLock();

	ReadLockHandle* readLock();
	WriteLockHandle* writeLock();

	void unclockHandle(AbstractLockHandle* handle) noexcept;
private:
	void readUnlock(ReadLockHandle* handle) noexcept;
	void writeUnlock(WriteLockHandle* handle) noexcept;

private:
	ConcurrentGate* gate;

	HashMap<CdbOid, ReadLockHandle> readHandles;
	HashMap<CdbOid, WriteLockHandle> writeHandles;
	SysMutex* hashMutex;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_ABSTRACTDATABASELOCK_H_ */
