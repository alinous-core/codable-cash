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

	void incRef() noexcept;

	const CdbOid* getThreadId() const noexcept {
		return threadId;
	}

protected:
	CdbOid* threadId;
	AbstractDatabaseLock* lock;
	int ref;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_ABSTRACTLOCKHANDLE_H_ */
