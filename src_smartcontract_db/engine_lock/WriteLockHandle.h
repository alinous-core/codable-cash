/*
 * WriteLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_WRITELOCKHANDLE_H_
#define ENGINE_LOCK_WRITELOCKHANDLE_H_

namespace codablecash {

class WriteLockHandle {
public:
	WriteLockHandle();
	virtual ~WriteLockHandle();
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_WRITELOCKHANDLE_H_ */
