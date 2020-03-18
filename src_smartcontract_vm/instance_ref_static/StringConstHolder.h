/*
 * StringConstHolder.h
 *
 *  Created on: 2020/03/18
 *      Author: iizuka
 */

#ifndef INSTANCE_REF_STATIC_STRINGCONSTHOLDER_H_
#define INSTANCE_REF_STATIC_STRINGCONSTHOLDER_H_

namespace alinous {

class VmStringInstance;
class UnicodeString;
class VirtualMachine;
class VmRootReference;

class StringConstHolder {
public:
	StringConstHolder();
	virtual ~StringConstHolder();

	VmStringInstance* newStringConstInstance(const UnicodeString* str, VirtualMachine* vm);
	void removeInnerReferences(VmRootReference* rootRef, VirtualMachine* vm) noexcept;
};

} /* namespace alinous */

#endif /* INSTANCE_REF_STATIC_STRINGCONSTHOLDER_H_ */
