/*
 * VariableIdentifier.cpp
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#include "sc_expression/VariableIdentifier.h"
#include "base/UnicodeString.h"

namespace alinous {

VariableIdentifier::VariableIdentifier() : AbstractExpression(CodeElement::EXP_VARIABLE_ID) {
	this->name = nullptr;
}

VariableIdentifier::~VariableIdentifier() {
	delete this->name;
}

void VariableIdentifier::setName(UnicodeString* name) noexcept {
	this->name = name;
}

} /* namespace alinous */
