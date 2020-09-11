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

class AbstractLockHandle {
public:
	explicit AbstractLockHandle(const CdbOid* threadId);
	virtual ~AbstractLockHandle();

private:
	CdbOid* threadId;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_ABSTRACTLOCKHANDLE_H_ */
