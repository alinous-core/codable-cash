/*
 * ReadLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_READLOCKHANDLE_H_
#define ENGINE_LOCK_READLOCKHANDLE_H_

namespace codablecash {

class ReadLockHandle {
public:
	ReadLockHandle();
	virtual ~ReadLockHandle();
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_READLOCKHANDLE_H_ */
