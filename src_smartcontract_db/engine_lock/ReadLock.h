/*
 * ReadLock.h
 *
 *  Created on: 2020/09/11
 *      Author: iizuka
 */

#ifndef ENGINE_LOCK_READLOCK_H_
#define ENGINE_LOCK_READLOCK_H_

namespace codablecash {

class ReadLock {
public:
	ReadLock();
	virtual ~ReadLock();
};

} /* namespace codablecash */

#endif /* ENGINE_LOCK_READLOCK_H_ */
