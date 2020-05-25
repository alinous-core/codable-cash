/*
 * DatabaseExceptionClassDeclare.cpp
 *
 *  Created on: 2020/05/25
 *      Author: iizuka
 */

#include "transaction_exception/DatabaseExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "instance_exception_class/ExceptionClassDeclare.h"
#include "instance_exception_class/ExceptionInstanceFactory.h"
#include "instance_exception_class/VmExceptionInstance.h"

#include "sc_declare/ClassExtends.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/IVmInstanceFactory.h"

#include "vm/VirtualMachine.h"

#include "sc/CodeElement.h"

#include "reserved_classes/ReservedClassRegistory.h"


namespace alinous {

UnicodeString DatabaseExceptionClassDeclare::NAME{L"DatabaseException"};

AnalyzedClass* DatabaseExceptionClassDeclare::createAnalyzedClass() noexcept {
	DatabaseExceptionClassDeclare* classDec = new DatabaseExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
}

void DatabaseExceptionClassDeclare::throwException(const UnicodeString* msg, VirtualMachine* vm, const CodeElement* element) noexcept {
	ExecControlManager* ctrl = vm->getCtrl();
	IVmInstanceFactory* factory = ExceptionInstanceFactory::getInstance();

	AnalyzedClass* aclass = vm->getReservedClassRegistory()->getAnalyzedClass(&NAME);

	VmClassInstance* inst = factory->createInstance(aclass, vm);
	inst->init(vm);


	VmExceptionInstance* exception = dynamic_cast<VmExceptionInstance*>(inst);

	vm->throwException(exception, element);
}

DatabaseExceptionClassDeclare::DatabaseExceptionClassDeclare() : AbstractExceptionClassDeclare() {
	addDefaultConstructor(&NAME);

	this->extends = new ClassExtends();
	this->extends->setClassName(&ExceptionClassDeclare::NAME);
}

DatabaseExceptionClassDeclare::~DatabaseExceptionClassDeclare() {

}

const UnicodeString* DatabaseExceptionClassDeclare::getName() noexcept {
	return &NAME;
}

const UnicodeString* DatabaseExceptionClassDeclare::getFullQualifiedName() noexcept {
	return &NAME;
}

ClassDeclare* DatabaseExceptionClassDeclare::getBaseClass() const noexcept {
	AnalyzedType* atype = this->extends->getAnalyzedType();
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	return aclass->getClassDeclare();
}

IVmInstanceFactory* DatabaseExceptionClassDeclare::getFactory() const noexcept {
	return ExceptionInstanceFactory::getInstance();
}

} /* namespace alinous */
