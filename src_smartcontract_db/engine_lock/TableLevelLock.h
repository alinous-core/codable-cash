/*
 * TableLevelLock.h
 *
 *  Created on: 2020/09/30
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_TABLELEVELLOCK_H_
#define ENGINE_LOCK_TABLELEVELLOCK_H_

#include "engine_lock/AbstractDatabaseLock.h"

namespace codablecash {

class TableLevelLock : public AbstractDatabaseLock {
public:
	TableLevelLock();
	virtual ~TableLevelLock();
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_TABLELEVELLOCK_H_ */
