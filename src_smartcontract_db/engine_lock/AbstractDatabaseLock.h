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
}
using namespace alinous;

namespace codablecash {

class CdbOid;
class ReadLockHandle;
class WriteLockHandle;

class AbstractDatabaseLock {
public:
	friend class ReadLockHandle;
	friend class WriteLockHandle;

	AbstractDatabaseLock();
	virtual ~AbstractDatabaseLock();

	ReadLockHandle* readLock();

	WriteLockHandle* writeLock();

private:
	void readUnlock(const ReadLockHandle* handle) noexcept;
	void writeUnlock(const WriteLockHandle* handle) noexcept;

private:
	ConcurrentGate* gate;

	HashMap<CdbOid, ReadLockHandle> readHandles;
	HashMap<CdbOid, WriteLockHandle> writeHandles;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_ABSTRACTDATABASELOCK_H_ */
