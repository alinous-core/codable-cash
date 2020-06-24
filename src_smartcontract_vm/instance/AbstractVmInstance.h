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

#include "instance/VmAllocatee.h"

namespace alinous {

class VirtualMachine;
class AbstractReference;
class GcManager;
class AbstractExtObject;
class VTableRegistory;
class IAbstractVmInstanceSubstance;
class AnalyzedType;

class AbstractVmInstance {
public:
	void* operator new(size_t size, VirtualMachine* vm);
	void operator delete(void* p, size_t size);

	explicit AbstractVmInstance(uint8_t type);
	virtual ~AbstractVmInstance();

	virtual uint8_t getType() const noexcept;
	virtual int hashCode() const noexcept;

	virtual const VMemList<AbstractReference>* getReferences() const noexcept;
	virtual IAbstractVmInstanceSubstance* getInstance() noexcept = 0;
	virtual bool isReference() const noexcept;
	virtual bool isNull() const noexcept;
	virtual int valueCompare(IAbstractVmInstanceSubstance* right) = 0;
	virtual const UnicodeString* toString() noexcept = 0;

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
protected:
	uint8_t type;
};

} /* namespace alinous */

#endif /* INSTANCE_ABSTRACTVMINSTANCE_H_ */
