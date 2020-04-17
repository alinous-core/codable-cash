/*
 * ArrayOutOfBoundsExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedClass.h"
#include "sc_analyze/AnalyzedType.h"

#include "instance_exception_class/ExceptionInstanceFactory.h"
#include "instance_exception_class/ExceptionClassDeclare.h"

#include "sc_declare/ClassExtends.h"


namespace alinous {

UnicodeString ArrayOutOfBoundsExceptionClassDeclare::NAME{L"ArrayOutOfBoundsException"};

ArrayOutOfBoundsExceptionClassDeclare::ArrayOutOfBoundsExceptionClassDeclare() : AbstractReservedClassDeclare() {
	addDefaultConstructor(&NAME);

	this->extends = new ClassExtends();
	this->extends->setClassName(&ExceptionClassDeclare::NAME);
}

AnalyzedClass* ArrayOutOfBoundsExceptionClassDeclare::createAnalyzedClass() noexcept {
	ArrayOutOfBoundsExceptionClassDeclare* classDec = new ArrayOutOfBoundsExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
}

ArrayOutOfBoundsExceptionClassDeclare::~ArrayOutOfBoundsExceptionClassDeclare() {

}

const UnicodeString* ArrayOutOfBoundsExceptionClassDeclare::getName() noexcept {
	return &NAME;
}

const UnicodeString* ArrayOutOfBoundsExceptionClassDeclare::getFullQualifiedName() noexcept {
	return &NAME;
}

ClassDeclare* ArrayOutOfBoundsExceptionClassDeclare::getBaseClass() const noexcept {
	AnalyzedType* atype = this->extends->getAnalyzedType();
	AnalyzedClass* aclass = atype->getAnalyzedClass();

	return aclass->getClassDeclare();
}

IVmInstanceFactory* ArrayOutOfBoundsExceptionClassDeclare::getFactory() const noexcept {
	return ExceptionInstanceFactory::getInstance();
}

} /* namespace alinous */
