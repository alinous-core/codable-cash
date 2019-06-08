/*
 * VmClassInstance.h
 *
 *  Created on: 2019/01/16
 *      Author: iizuka
 */

#ifndef INSTANCE_VMCLASSINSTANCE_H_
#define INSTANCE_VMCLASSINSTANCE_H_

#include "instance/AbstractVmInstance.h"

namespace alinous {

class AnalyzedClass;

class VmClassInstance : public AbstractVmInstance {
public:
	VmClassInstance(AnalyzedClass* clazz);
	virtual ~VmClassInstance();

private:
	AnalyzedClass* const clazz;
};

} /* namespace alinous */

#endif /* INSTANCE_VMCLASSINSTANCE_H_ */
