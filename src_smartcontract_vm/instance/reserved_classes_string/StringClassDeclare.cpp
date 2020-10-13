/*
 * StringClassDeclare.cpp
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#include "instance/reserved_classes_string/StringClassDeclare.h"

#include "base/UnicodeString.h"

#include "engine/sc_analyze/AnalyzedClass.h"

namespace alinous {

UnicodeString StringClassDeclare::NAME{L"String"};

StringClassDeclare::StringClassDeclare() : AbstractReservedClassDeclare() {

}

StringClassDeclare::~StringClassDeclare() {
}

const UnicodeString* StringClassDeclare::getName() noexcept {
	return &NAME;
}

const UnicodeString* StringClassDeclare::getFullQualifiedName() noexcept {
	return &NAME;
}

AnalyzedClass* StringClassDeclare::createAnalyzedClass() noexcept {
	StringClassDeclare* classDec = new StringClassDeclare();
	AnalyzedClass* aclass = new AnalyzedClass(classDec);

	return aclass;
}

ClassDeclare* StringClassDeclare::getBaseClass() const noexcept {
	return nullptr;
}

} /* namespace alinous */
