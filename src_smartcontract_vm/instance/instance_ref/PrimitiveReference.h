/*
 * PrimitiveReference.h
 *
 *  Created on: 2019/05/25
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_PRIMITIVEREFERENCE_H_
#define INSTANCE_REF_PRIMITIVEREFERENCE_H_

#include "instance/instance_ref/AbstractReference.h"
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

	virtual IAbstractVmInstanceSubstance* getInstance() noexcept;

	virtual bool isPrimitive() const noexcept;
	virtual int valueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;
	virtual int hashCode() const noexcept;

	virtual void substitute(IAbstractVmInstanceSubstance* rightValue, VirtualMachine* vm);
	virtual void resetOnGc() noexcept;

	virtual AbstractReference* wrap(IAbstractVmInstanceSubstance* owner, VirtualMachine* vm);
	virtual uint8_t getInstType() const noexcept;
	virtual AnalyzedType getRuntimeType() const noexcept;

	virtual const VMemList<AbstractReference>* getInstReferences() const noexcept;
	virtual int instHashCode() const noexcept;
	virtual bool instIsPrimitive() const noexcept;
	virtual bool instIsNull() const noexcept;
	virtual int instValueCompare(const IAbstractVmInstanceSubstance* right) const noexcept;
	virtual AbstractExtObject* instToClassExtObject(const UnicodeString* name, VTableRegistory* table);

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* table);
	virtual const UnicodeString* toString() const noexcept;

	virtual bool isStaticConst() const noexcept;

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

	VmMalloc* getMalloc() {
		return malloc;
	}
	void* getData() {
		return this->data;
	}

	PrimitiveReference* copy(VirtualMachine* vm) const noexcept;


	class ValueCompare {
	public:
		int operator() (const PrimitiveReference* const _this, const  PrimitiveReference* const object) noexcept;
	};

private:
	int valueCompare8(const PrimitiveReference* right) const noexcept;
	int valueCompare16(const PrimitiveReference* right) const noexcept;
	int valueCompare32(const PrimitiveReference* right) const noexcept;
	int valueCompare64(const PrimitiveReference* right) const noexcept;

protected:
	static size_t getDataSize(int8_t type) noexcept;

protected:
	void* data;
	VmMalloc* malloc;

	mutable UnicodeString* str;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_PRIMITIVEREFERENCE_H_ */
