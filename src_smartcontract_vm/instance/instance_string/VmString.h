/*
 * VmString.h
 *
 *  Created on: 2020/03/17
 *      Author: iizuka
 */

#ifndef INSTANCE_STRING_VMSTRING_H_
#define INSTANCE_STRING_VMSTRING_H_

#include "instance/VmAllocatee.h"

#include "instance/instance_parts/VMemPrimitiveList.h"

namespace alinous {

class UnicodeString;
class VirtualMachine;

class VmString : public VmAllocatee {
public:
	VmString(VirtualMachine* vm, const UnicodeString* str);
	virtual ~VmString();

	int length() const noexcept;
	wchar_t charAt(int index) const noexcept;

	const wchar_t* towString() const noexcept;
	int hashCode() const noexcept;
private:
	VmString* __append(wchar_t ch) noexcept;
	void __closeString() noexcept;
private:
	VMemPrimitiveList<wchar_t> *buff;
	int __hashCode;

public:
	class ValueCompare {
	public:
		int operator () (const VmString* const a, const VmString* const b) const;
	};
};

} /* namespace alinous */

#endif /* INSTANCE_STRING_VMSTRING_H_ */
