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
	explicit AbstractVmInstance(uint8_t type);
	virtual ~AbstractVmInstance();

	void* operator new(size_t size, VirtualMachine* vm);
	void operator delete(void* p, size_t size);

	uint8_t getType() const noexcept;
	int hashCode() const noexcept;

	virtual const VMemList<AbstractReference>* getReferences() const noexcept;
	virtual bool isReference() const noexcept;
private:
	uint8_t type;
};

} /* namespace alinous */

#endif /* INSTANCE_ABSTRACTVMINSTANCE_H_ */
