/*
 * ZeroDivisionExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/ZeroDivisionExceptionClassDeclare.h"

#include "instance_exception_class/ExceptionInstanceFactory.h"
#include "instance_exception_class/ExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/IVmInstanceFactory.h"

#include "sc_declare/ClassExtends.h"

#include "vm/VirtualMachine.h"

#include "vm_ctrl/ExecControlManager.h"

#include "instance/VmClassInstance.h"

#include "reserved_classes/ReservedClassRegistory.h"

#include "instance_exception_class/VmExceptionInstance.h"

namespace alinous {

UnicodeString ZeroDivisionExceptionClassDeclare::NAME{L"ZeroDivisionException"};

ZeroDivisionExceptionClassDeclare::ZeroDivisionExceptionClassDeclare() : AbstractExceptionClassDeclare() {
	addDefaultConstructor(&NAME);

	this->extends = new ClassExtends();
	this->extends->setClassName(&ExceptionClassDeclare::NAME);
}

AnalyzedClass* ZeroDivisionExceptionClassDeclare::createAnalyzedClass() noexcept {
	ZeroDivisionExceptionClassDeclare* classDec = new ZeroDivisionExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	classDec->setAnalyzedClass(aclass);

	return aclass;
}

void ZeroDivisionExceptionClassDeclare::throwException(VirtualMachine* vm, const CodeElement* element) noexcept {
	ExecControlManager* ctrl = vm->getCtrl();
	IVmInstanceFactory* factory = ExceptionInstanceFactory::getInstance();

	AnalyzedClass* aclass = ReservedClassRegistory::getInstance()->getAnalyzedClass(&NAME);

	VmClassInstance* inst = factory->createInstance(aclass, vm);
	inst->init(vm);


	VmExceptionInstance* exception = dynamic_cast<VmExceptionInstance*>(inst);

	vm->throwException(exception, element);
}

ZeroDivisionExceptionClassDeclare::~ZeroDivisionExceptionClassDeclare() {

}

const UnicodeString* ZeroDivisionExceptionClassDeclare::getName() noexcept {
	return &NAME;
}

const UnicodeString* ZeroDivisionExceptionClassDeclare::getFullQualifiedName() noexcept {
	return &NAME;
}

ClassDeclare* ZeroDivisionExceptionClassDeclare::getBaseClass() const noexcept {
	AnalyzedType* atype = this->extends->getAnalyzedType();
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	return aclass->getClassDeclare();
}

IVmInstanceFactory* ZeroDivisionExceptionClassDeclare::getFactory() const noexcept {
	return ExceptionInstanceFactory::getInstance();
}

} /* namespace alinous */
