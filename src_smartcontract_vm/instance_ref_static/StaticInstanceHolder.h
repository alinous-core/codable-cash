/*
 * StaticInstanceHolder.h
 *
 *  Created on: 2019/11/14
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_STATIC_STATICINSTANCEHOLDER_H_
#define INSTANCE_REF_STATIC_STATICINSTANCEHOLDER_H_
#include <cstdint>

namespace alinous {

class NumericConstHolder;
class PrimitiveReference;
class VirtualMachine;
class VmRootReference;
class UnicodeString;
class StringConstHolder;
class VmStringInstance;

class StaticInstanceHolder {
public:
	StaticInstanceHolder();
	virtual ~StaticInstanceHolder();

	PrimitiveReference* newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm);
	VmStringInstance* newStringConstInstance(VmRootReference* rootRef, const UnicodeString* str, VirtualMachine* vm);

	void removeStringConst(VmRootReference* rootRef, VirtualMachine* vm) noexcept;
	void removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept;
private:
	NumericConstHolder* numeric;
	StringConstHolder* stringConsts;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_STATIC_STATICINSTANCEHOLDER_H_ */
