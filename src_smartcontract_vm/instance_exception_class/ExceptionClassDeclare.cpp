/*
 * ExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/12
 *      Author: iizuka
 */

#include "instance_exception_class/ExceptionClassDeclare.h"
#include "instance_exception_class/ExceptionInstanceFactory.h"

#include "sc_analyze/AnalyzedClass.h"

#include "base/UnicodeString.h"


namespace alinous {

UnicodeString ExceptionClassDeclare::NAME{L"Exception"};

ExceptionClassDeclare::ExceptionClassDeclare() : AbstractReservedClassDeclare() {
	addDefaultConstructor(&NAME);
}

ExceptionClassDeclare::~ExceptionClassDeclare() {

}

AnalyzedClass* ExceptionClassDeclare::createAnalyzedClass() noexcept {
	ExceptionClassDeclare* classDec = new ExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);
	aclass->setFactory(ExceptionInstanceFactory::getInstance());

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

} /* namespace alinous */
