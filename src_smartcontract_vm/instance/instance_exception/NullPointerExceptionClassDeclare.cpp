/*
 * NullPointerExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "engine/sc_analyze/AnalyzedClass.h"
#include "engine/sc_analyze/AnalyzedType.h"
#include "engine/sc_analyze/IVmInstanceFactory.h"

#include "instance/instance_exception_class/ExceptionInstanceFactory.h"
#include "instance/instance_exception_class/ExceptionClassDeclare.h"
#include "instance/instance_exception_class/VmExceptionInstance.h"

#include "lang/sc_declare/ClassExtends.h"

#include "vm/vm_ctrl/ExecControlManager.h"

#include "vm/VirtualMachine.h"

#include "instance/reserved_classes/ReservedClassRegistory.h"


namespace alinous {

UnicodeString NullPointerExceptionClassDeclare::NAME{L"NullPointerException"};

NullPointerExceptionClassDeclare::NullPointerExceptionClassDeclare() : AbstractExceptionClassDeclare() {
	addDefaultConstructor(&NAME);

	this->extends = new ClassExtends();
	this->extends->setClassName(&ExceptionClassDeclare::NAME);
}

AnalyzedClass* NullPointerExceptionClassDeclare::createAnalyzedClass() noexcept {
	NullPointerExceptionClassDeclare* classDec = new NullPointerExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
}

void NullPointerExceptionClassDeclare::throwException(VirtualMachine* vm, const CodeElement* element) noexcept {
	ExecControlManager* ctrl = vm->getCtrl();
	IVmInstanceFactory* factory = ExceptionInstanceFactory::getInstance();

	AnalyzedClass* aclass = vm->getReservedClassRegistory()->getAnalyzedClass(&NAME);

	VmClassInstance* inst = factory->createInstance(aclass, vm);
	inst->init(vm);


	VmExceptionInstance* exception = dynamic_cast<VmExceptionInstance*>(inst);

	vm->throwException(exception, element);
}

NullPointerExceptionClassDeclare::~NullPointerExceptionClassDeclare() {

}

const UnicodeString* NullPointerExceptionClassDeclare::getName() noexcept {
	return &NAME;
}

const UnicodeString* NullPointerExceptionClassDeclare::getFullQualifiedName() noexcept {
	return &NAME;
}

ClassDeclare* NullPointerExceptionClassDeclare::getBaseClass() const noexcept {
	AnalyzedType* atype = this->extends->getAnalyzedType();
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	return aclass->getClassDeclare();
}

IVmInstanceFactory* NullPointerExceptionClassDeclare::getFactory() const noexcept {
	return ExceptionInstanceFactory::getInstance();
}

} /* namespace alinous */
