/*
 * VmExceptionInstance.h
 *
 *  Created on: 2020/04/14
 *      Author: iizuka
 */

#ifndef INSTANCE_EXCEPTION_CLASS_VMEXCEPTIONINSTANCE_H_
#define INSTANCE_EXCEPTION_CLASS_VMEXCEPTIONINSTANCE_H_

#include "instance/VmClassInstance.h"

namespace alinous {

class VmExceptionInstance : public VmClassInstance {
public:
	VmExceptionInstance(AnalyzedClass* clazz, VirtualMachine* vm);
	virtual ~VmExceptionInstance();

	void setCodeElement(CodeElement* element) noexcept;
	CodeElement* getElement() const noexcept;
private:
	CodeElement* element;
};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_CLASS_VMEXCEPTIONINSTANCE_H_ */
