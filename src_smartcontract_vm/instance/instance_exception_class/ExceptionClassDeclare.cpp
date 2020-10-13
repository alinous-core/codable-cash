/*
 * ExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "instance/instance_exception_class/ExceptionClassDeclare.h"
#include "instance/instance_exception_class/ExceptionInstanceFactory.h"

#include "engine/sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"

#include "lang/sc_declare/MemberVariableDeclare.h"
#include "lang/sc_declare/AccessControlDeclare.h"

#include "lang/sc_declare_types/StringType.h"


namespace alinous {

UnicodeString ExceptionClassDeclare::NAME{L"Exception"};

ExceptionClassDeclare::ExceptionClassDeclare() : AbstractExceptionClassDeclare() {
	addDefaultConstructor(&NAME);

	MemberVariableDeclare* message = new MemberVariableDeclare();
	message->setAccessControl(AccessControlDeclare::PROTECTED);
	message->setType(new StringType());
	message->setName(new UnicodeString(L"message"));

	this->members->addElement(message);
}

ExceptionClassDeclare::~ExceptionClassDeclare() {

}

AnalyzedClass* ExceptionClassDeclare::createAnalyzedClass() noexcept {
	ExceptionClassDeclare* classDec = new ExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
}

const UnicodeString* ExceptionClassDeclare::getName() noexcept {
	return &NAME;
}

const UnicodeString* ExceptionClassDeclare::getFullQualifiedName() noexcept {
	return &NAME;
}

ClassDeclare* ExceptionClassDeclare::getBaseClass() const noexcept {
	return nullptr;
}

IVmInstanceFactory* ExceptionClassDeclare::getFactory() const noexcept {
	return ExceptionInstanceFactory::getInstance();
}

} /* namespace alinous */
