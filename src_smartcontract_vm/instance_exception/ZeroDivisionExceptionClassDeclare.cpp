/*
 * ZeroDivisionExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/ZeroDivisionExceptionClassDeclare.h"

#include "instance_exception_class/ExceptionInstanceFactory.h"

#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedClass.h"


namespace alinous {

UnicodeString ZeroDivisionExceptionClassDeclare::NAME{L"ZeroDivisionException"};

ZeroDivisionExceptionClassDeclare::ZeroDivisionExceptionClassDeclare() : AbstractReservedClassDeclare() {
	addDefaultConstructor(&NAME);
}

AnalyzedClass* ZeroDivisionExceptionClassDeclare::createAnalyzedClass() noexcept {
	ZeroDivisionExceptionClassDeclare* classDec = new ZeroDivisionExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
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
}

IVmInstanceFactory* ZeroDivisionExceptionClassDeclare::getFactory() const  noexcept{
	return ExceptionInstanceFactory::getInstance();
}

} /* namespace alinous */
