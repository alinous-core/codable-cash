/*
 * ZeroDivisionExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/ZeroDivisionExceptionClassDeclare.h"

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

} /* namespace alinous */
