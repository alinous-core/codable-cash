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
#include "instance_parts/VMemList.h"

namespace alinous {

class VirtualMachine;
class AbstractReference;
class GcManager;

class AbstractVmInstance {
public:
	static constexpr uint8_t STACK {1};
	static constexpr uint8_t ISNT_OBJ {2};
	static constexpr uint8_t INST_STRING{3};
	static constexpr uint8_t INST_BIG_INT{4};
	static constexpr uint8_t INST_ARRAY{5};


	static constexpr uint8_t REF_ROOT{100};
	static constexpr uint8_t REF_OBJ{101};
	static constexpr uint8_t REF_BYTE{102};
	static constexpr uint8_t REF_CHAR{103};
	static constexpr uint8_t REF_SHORT{104};
	static constexpr uint8_t REF_INT{105};
	static constexpr uint8_t REF_LONG{106};


	explicit AbstractVmInstance(uint8_t type);
	virtual ~AbstractVmInstance();

	void* operator new(size_t size, VirtualMachine* vm);
	void operator delete(void* p, size_t size);

	uint8_t getType() const noexcept;
	int hashCode() const noexcept;

	virtual const VMemList<AbstractReference>* getReferences() const noexcept;
private:
	uint8_t type;
};

} /* namespace alinous */

#endif /* INSTANCE_ABSTRACTVMINSTANCE_H_ */
