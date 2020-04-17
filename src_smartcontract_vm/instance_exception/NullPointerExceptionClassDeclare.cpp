/*
 * NullPointerExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/NullPointerExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedClass.h"

#include "instance_exception_class/ExceptionInstanceFactory.h"

namespace alinous {

UnicodeString NullPointerExceptionClassDeclare::NAME{L"NullPointerException"};

NullPointerExceptionClassDeclare::NullPointerExceptionClassDeclare() : AbstractReservedClassDeclare() {
	addDefaultConstructor(&NAME);
}

AnalyzedClass* NullPointerExceptionClassDeclare::createAnalyzedClass() noexcept {
	NullPointerExceptionClassDeclare* classDec = new NullPointerExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
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
}

IVmInstanceFactory* NullPointerExceptionClassDeclare::getFactory() const noexcept {
	return ExceptionInstanceFactory::getInstance();
}

} /* namespace alinous */
