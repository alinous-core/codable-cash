/*
 * NumericConstHolder.h
 *
 *  Created on: 2019/11/14
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_STATIC_NUMERICCONSTHOLDER_H_
#define INSTANCE_REF_STATIC_NUMERICCONSTHOLDER_H_
#include <cstdint>

#include "base/HashMap.h"
#include "instance_ref_static/LongIntegerKey.h"

namespace alinous {

class PrimitiveReference;
class VirtualMachine;
class LongIntegerKey;
class VmRootReference;

class NumericConstHolder {
public:
	NumericConstHolder();
	virtual ~NumericConstHolder();

	PrimitiveReference* newNumericConstReferenece(int64_t value, uint8_t type, VirtualMachine* vm);

	void removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept;
private:
	HashMap<LongIntegerKey, PrimitiveReference> intVariables;
	HashMap<LongIntegerKey, PrimitiveReference> longVariables;

};

} /* namespace alinous */

#endif /* INSTANCE_REF_STATIC_NUMERICCONSTHOLDER_H_ */
