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
	AbstractDatabaseLock();
	virtual ~AbstractDatabaseLock();

	ReadLockHandle* readLock();

	WriteLockHandle* writeLock();
private:
	ConcurrentGate* gate;

	HashMap<CdbOid, ReadLockHandle> map;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_ABSTRACTDATABASELOCK_H_ */
