/*
 * AbstractLockHandle.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_ABSTRACTLOCKHANDLE_H_
#define ENGINE_LOCK_ABSTRACTLOCKHANDLE_H_

namespace codablecash {

class CdbOid;
class AbstractDatabaseLock;

class AbstractLockHandle {
public:
	AbstractLockHandle(const CdbOid* threadId, AbstractDatabaseLock* lock);
	virtual ~AbstractLockHandle();

private:
	CdbOid* threadId;
	AbstractDatabaseLock* lock;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_ABSTRACTLOCKHANDLE_H_ */
