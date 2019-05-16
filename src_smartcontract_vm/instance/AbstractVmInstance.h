/*
 * AbstractVmInstance.h
 *
 *  Created on: 2019/05/02
 *      Author: iizuka
 */

#ifndef INSTANCE_ABSTRACTVMINSTANCE_H_
#define INSTANCE_ABSTRACTVMINSTANCE_H_
#include <cstddef>

namespace alinous {

class VirtualMachine;

class AbstractVmInstance {
public:
	AbstractVmInstance();
	virtual ~AbstractVmInstance();

	void* operator new(size_t size, VirtualMachine* vm);
	void operator delete(void* p, size_t size);
};

} /* namespace alinous */

#endif /* INSTANCE_ABSTRACTVMINSTANCE_H_ */
