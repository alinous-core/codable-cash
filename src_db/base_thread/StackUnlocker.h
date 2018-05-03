/*
 * StackUnlocker.h
 *
 *  Created on: 2018/04/27
 *      Author: iizuka
 */

#ifndef BASE_THREAD_STACKUNLOCKER_H_
#define BASE_THREAD_STACKUNLOCKER_H_

namespace alinous {

class ILock;

class StackUnlocker {
public:
	explicit StackUnlocker(ILock* mutex) noexcept;
	virtual ~StackUnlocker() noexcept;
private:
	ILock* mutex;
};

} /* namespace alinous */

#endif /* BASE_THREAD_STACKUNLOCKER_H_ */
