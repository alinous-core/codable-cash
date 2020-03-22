/*
 * PrimitiveReference.h
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_PRIMITIVEREFERENCE_H_
#define INSTANCE_REF_PRIMITIVEREFERENCE_H_

#include "instance_ref/AbstractReference.h"
#include "instance/IAbstractVmInstanceSubstance.h"

namespace alinous {

class PrimitiveReference : public AbstractReference, public IAbstractVmInstanceSubstance {
public:
	explicit PrimitiveReference(uint8_t type);
	virtual ~PrimitiveReference();

	static PrimitiveReference* createBoolReference(VirtualMachine* vm, int8_t value);
	static PrimitiveReference* createByteReference(VirtualMachine* vm, int8_t value);
	static PrimitiveReference* createCharReference(VirtualMachine* vm, int16_t value);
	static PrimitiveReference* createShortReference(VirtualMachine* vm, int16_t value);
	static PrimitiveReference* createIntReference(VirtualMachine* vm, int32_t value);
	static PrimitiveReference* createLongReference(VirtualMachine* vm, int64_t value);

	virtual bool isPrimitive() const noexcept;
	virtual int valueCompare(AbstractVmInstance* right);

	virtual void substitute(AbstractVmInstance* rightValue, VirtualMachine* vm);
	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm) const;

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);

	bool getBoolValue() const noexcept;

	int32_t getIntValue() const noexcept;
	void setIntValue(int32_t value) noexcept;

	int8_t getByteValue() const noexcept;
	void setByteValue(int8_t value) noexcept;
	int16_t getShortValue() const noexcept;
	void setShortValue(int16_t value) noexcept;
	int16_t getCharValue() const noexcept;
	void setCharValue(int16_t value) noexcept;
	int64_t getLongValue() const noexcept;
	void setLongValue(int64_t value) noexcept;

private:
	int valueCompare8(PrimitiveReference* right);
	int valueCompare16(PrimitiveReference* right);
	int valueCompare32(PrimitiveReference* right);
	int valueCompare64(PrimitiveReference* right);

private:
	void* data;
	VmMalloc* malloc;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_PRIMITIVEREFERENCE_H_ */
