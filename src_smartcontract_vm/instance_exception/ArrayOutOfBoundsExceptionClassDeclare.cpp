/*
 * ArrayOutOfBoundsExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedClass.h"


namespace alinous {

UnicodeString ArrayOutOfBoundsExceptionClassDeclare::NAME{L"ArrayOutOfBoundsException"};

ArrayOutOfBoundsExceptionClassDeclare::ArrayOutOfBoundsExceptionClassDeclare() : AbstractReservedClassDeclare() {
	addDefaultConstructor(&NAME);
}

AnalyzedClass* ArrayOutOfBoundsExceptionClassDeclare::createAnalyzedClass() noexcept {
	ArrayOutOfBoundsExceptionClassDeclare* classDec = new ArrayOutOfBoundsExceptionClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
}

ArrayOutOfBoundsExceptionClassDeclare::~ArrayOutOfBoundsExceptionClassDeclare() {

}

} /* namespace alinous */
