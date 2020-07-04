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

	void setCodeElement(const CodeElement* element) noexcept;
	const CodeElement* getElement() const noexcept;

	void setMessage(const UnicodeString* message) noexcept;
	const UnicodeString* getMessage() const noexcept {
		return this->message;
	}

	virtual AbstractExtObject* toClassExtObject(const UnicodeString* name, VTableRegistory* reg);
	virtual const UnicodeString* toString() noexcept;
private:
	const CodeElement* element;
	UnicodeString* message;

};

} /* namespace alinous */

#endif /* INSTANCE_EXCEPTION_CLASS_VMEXCEPTIONINSTANCE_H_ */
