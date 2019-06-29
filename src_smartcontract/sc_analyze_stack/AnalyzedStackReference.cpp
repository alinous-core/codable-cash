/*
 * AnalyzedStackReference.cpp
 *
 *  Created on: 2019/06/12
 *      Author: iizuka
 */

#include "sc_analyze_stack/AnalyzedStackReference.h"
#include "sc_analyze/AnalyzedType.h"

#include "base/UnicodeString.h"

namespace alinous {

AnalyzedStackReference::AnalyzedStackReference(const UnicodeString* name, const AnalyzedType* type) {
	this->name = new UnicodeString(*name);
	this->type = new AnalyzedType(*type);
}

AnalyzedStackReference::~AnalyzedStackReference() {
	delete this->name;
	delete this->type;
}

const UnicodeString* alinous::AnalyzedStackReference::getName() noexcept {
	return this->name;
}


} /* namespace alinous */
