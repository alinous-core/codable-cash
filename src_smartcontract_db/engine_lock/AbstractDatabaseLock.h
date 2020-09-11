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
class ReadLock;
class WriteLock;

class AbstractDatabaseLock {
public:
	AbstractDatabaseLock();
	virtual ~AbstractDatabaseLock();

	ReadLock* readLock();

	WriteLock* writeLock();
private:
	ConcurrentGate* gate;

	HashMap<CdbOid, ReadLock> map;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_ABSTRACTDATABASELOCK_H_ */
