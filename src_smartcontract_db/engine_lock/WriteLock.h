/*
 * WriteLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_WRITELOCK_H_
#define ENGINE_LOCK_WRITELOCK_H_

namespace codablecash {

class WriteLock {
public:
	WriteLock();
	virtual ~WriteLock();
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_WRITELOCK_H_ */
