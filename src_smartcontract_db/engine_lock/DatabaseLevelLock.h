/*
 * DatabaseLevelLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_DATABASELEVELLOCK_H_
#define ENGINE_LOCK_DATABASELEVELLOCK_H_

#include "engine_lock/AbstractDatabaseLock.h"

namespace codablecash {

class DatabaseLevelLock : public AbstractDatabaseLock {
public:
	DatabaseLevelLock();
	virtual ~DatabaseLevelLock();
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_DATABASELEVELLOCK_H_ */
