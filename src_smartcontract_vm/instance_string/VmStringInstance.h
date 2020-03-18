/*
 * VmStringInstance.h
 *
 *  Created on: 2019/05/27
 *      Author: iizuka
 */

#ifndef INSTANCE_VMSTRINGINSTANCE_H_
#define INSTANCE_VMSTRINGINSTANCE_H_

#include "instance/AbstractVmInstance.h"


namespace alinous {

class VmString;
class VirtualMachine;

class VmStringInstance : public AbstractVmInstance {
public:
	VmStringInstance(VirtualMachine* vm, const UnicodeString* str);
	virtual ~VmStringInstance();

	virtual int valueCompare(AbstractVmInstance* right);
private:
	VmString* value;
};

} /* namespace alinous */

#endif /* INSTANCE_VMSTRINGINSTANCE_H_ */
