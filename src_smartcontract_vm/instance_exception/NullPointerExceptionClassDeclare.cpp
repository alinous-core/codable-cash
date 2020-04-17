/*
 * NullPointerExceptionClassDeclare.cpp
 *
 *  Created on: 2020/04/17
 *      Author: iizuka
 */

#include "instance_exception/NullPointerExceptionClassDeclare.h"

#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedClass.h"


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

} /* namespace alinous */
