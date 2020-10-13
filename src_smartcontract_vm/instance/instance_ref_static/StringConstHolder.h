/*
 * StringConstHolder.h
 *
 *  Created on: 2020/03/18
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_STATIC_STRINGCONSTHOLDER_H_
#define INSTANCE_REF_STATIC_STRINGCONSTHOLDER_H_

#include "base/HashMap.h"

namespace alinous {

class VmStringInstance;
class UnicodeString;
class VirtualMachine;
class VmRootReference;
class AbstractReference;

class StringConstHolder {
public:
	StringConstHolder();
	virtual ~StringConstHolder();

	VmStringInstance* newStringConstInstance(VmRootReference* rootRef, const UnicodeString* str, VirtualMachine* vm);
	void removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept;

private:
	HashMap<UnicodeString, AbstractReference> stringVariables;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_STATIC_STRINGCONSTHOLDER_H_ */
