/*
 * StackDbLockUnlocker.h
 *
 *  Created on: 2020/09/30
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_STACKDBLOCKUNLOCKER_H_
#define ENGINE_LOCK_STACKDBLOCKUNLOCKER_H_

namespace codablecash {

class AbstractDatabaseLock;
class AbstractLockHandle;

class StackDbLockUnlocker {
public:
	explicit StackDbLockUnlocker(AbstractDatabaseLock* lock);
	virtual ~StackDbLockUnlocker();

private:
	AbstractLockHandle* handle;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_STACKDBLOCKUNLOCKER_H_ */
