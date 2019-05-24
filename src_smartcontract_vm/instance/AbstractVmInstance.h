/*
 * AbstractVmInstance.h
 *
 *  Created on: 2019/05/02
 *      Author: iizuka
 */

#ifndef INSTANCE_ABSTRACTVMINSTANCE_H_
#define INSTANCE_ABSTRACTVMINSTANCE_H_
#include <cstddef>
#include <cstdint>

namespace alinous {

class VirtualMachine;

class AbstractVmInstance {
public:
	static constexpr uint8_t ISNT_OBJ {1};
	static constexpr uint8_t INST_STRING{2};
	static constexpr uint8_t INST_BIG_INT{3};

	AbstractVmInstance();
	virtual ~AbstractVmInstance();

	void* operator new(size_t size, VirtualMachine* vm);
	void operator delete(void* p, size_t size);

private:
	uint8_t type;
};

} /* namespace alinous */

#endif /* INSTANCE_ABSTRACTVMINSTANCE_H_ */
