/*
 * AbstractDatabaseLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_ABSTRACTDATABASELOCK_H_
#define ENGINE_LOCK_ABSTRACTDATABASELOCK_H_

namespace alinous {
class ConcurrentGate;
}
using namespace alinous;

namespace codablecash {

class AbstractDatabaseLock {
public:
	AbstractDatabaseLock();
	virtual ~AbstractDatabaseLock();

private:
	ConcurrentGate* gate;
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_ABSTRACTDATABASELOCK_H_ */
