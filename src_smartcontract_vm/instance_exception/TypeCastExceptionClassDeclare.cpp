/*
 * TypeCastException.cpp
 *
 *  Created on: 2020/04/23
 *      Author: iizuka
 */

#include "instance_exception/TypeCastExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/IVmInstanceFactory.h"

#include "instance_exception_class/ExceptionInstanceFactory.h"
#include "instance_exception_class/ExceptionClassDeclare.h"
#include "instance_exception_class/VmExceptionInstance.h"

#include "sc_declare/ClassExtends.h"

#include "vm_ctrl/ExecControlManager.h"

#include "vm/VirtualMachine.h"

#include "reserved_classes/ReservedClassRegistory.h"

namespace alinous {

UnicodeString TypeCastExceptionClassDeclare::NAME{L"TypeCastException"};

TypeCastExceptionClassDeclare::TypeCastExceptionClassDeclare() {
	addDefaultConstructor(&NAME);

	this->extends = new ClassExtends();
	this->extends->setClassName(&ExceptionClassDeclare::NAME);
}

AnalyzedClass* TypeCastExceptionClassDeclare::createAnalyzedClass() noexcept {
	TypeCastExceptionClassDeclare* classDec = new TypeCastExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
}

void TypeCastExceptionClassDeclare::throwException(VirtualMachine* vm, const CodeElement* element) noexcept {
	ExecControlManager* ctrl = vm->getCtrl();
	IVmInstanceFactory* factory = ExceptionInstanceFactory::getInstance();

	AnalyzedClass* aclass = vm->getReservedClassRegistory()->getAnalyzedClass(&NAME);

	VmClassInstance* inst = factory->createInstance(aclass, vm);
	inst->init(vm);


	VmExceptionInstance* exception = dynamic_cast<VmExceptionInstance*>(inst);

	vm->throwException(exception, element);
}

TypeCastExceptionClassDeclare::~TypeCastExceptionClassDeclare() {
}

const UnicodeString* TypeCastExceptionClassDeclare::getName() noexcept {
	return &NAME;
}

const UnicodeString* TypeCastExceptionClassDeclare::getFullQualifiedName() noexcept {
	return &NAME;
}

ClassDeclare* TypeCastExceptionClassDeclare::getBaseClass() const noexcept {
	AnalyzedType* atype = this->extends->getAnalyzedType();
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	return aclass->getClassDeclare();
}

IVmInstanceFactory* TypeCastExceptionClassDeclare::getFactory() const noexcept {
	return ExceptionInstanceFactory::getInstance();
}

} /* namespace alinous */