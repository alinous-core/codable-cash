/*
 * AnalyzedStackReference.cpp
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#include "engine/sc_analyze_stack/AnalyzedStackReference.h"
#include "engine/sc_analyze/AnalyzedType.h"

#include "base/UnicodeString.h"

namespace alinous {

const UnicodeString AnalyzedStackReference::THIS(L"this");

AnalyzedStackReference::AnalyzedStackReference(const UnicodeString* name, const AnalyzedType* type) {
	this->name = new UnicodeString(*name);
	this->type = new AnalyzedType(*type);
}

AnalyzedStackReference::~AnalyzedStackReference() {
	delete this->name;
	delete this->type;
}

const UnicodeString* AnalyzedStackReference::getName() const noexcept {
	return this->name;
}

const AnalyzedType* AnalyzedStackReference::getType() const noexcept {
	return this->type;
}


} /* namespace alinous */
