/*
 * VmClassInstance.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef INSTANCE_VMCLASSINSTANCE_H_
#define INSTANCE_VMCLASSINSTANCE_H_

#include "instance/AbstractVmInstance.h"
#include "instance_parts/VMemList.h"

namespace alinous {

class AnalyzedClass;
class AbstractReference;
class VirtualMachine;

class VmClassInstance : public AbstractVmInstance {
public:
	VmClassInstance(AnalyzedClass* clazz, VirtualMachine* vm);
	virtual ~VmClassInstance();

	static VmClassInstance* createObject(AnalyzedClass* clazz, VirtualMachine* vm);


private:
	void init(VirtualMachine* vm);

private:
	AnalyzedClass* const clazz;
	VMemList<AbstractReference> members;
};

} /* namespace alinous */

#endif /* INSTANCE_VMCLASSINSTANCE_H_ */
