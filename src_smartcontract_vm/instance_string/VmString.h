/*
 * VmString.h
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#ifndef INSTANCE_STRING_VMSTRING_H_
#define INSTANCE_STRING_VMSTRING_H_

#include "instance/VmAllocatee.h"

#include "instance_parts/VMemPrimitiveList.h"

namespace alinous {

class UnicodeString;
class VirtualMachine;

class VmString : public VmAllocatee {
public:
	VmString(VirtualMachine* vm, const UnicodeString* str);
	virtual ~VmString();

	VMemPrimitiveList<wchar_t> *buff;
};

} /* namespace alinous */

#endif /* INSTANCE_STRING_VMSTRING_H_ */
