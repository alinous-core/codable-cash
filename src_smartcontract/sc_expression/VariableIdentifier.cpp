/*
 * VariableIdentifier.cpp
 *
 *  Created on: 2019/02/12
 *      Author: iizuka
 */

#include "sc_expression/VariableIdentifier.h"
#include "base/UnicodeString.h"

#include "sc_analyze/AnalyzedType.h"

namespace alinous {

VariableIdentifier::VariableIdentifier() : AbstractExpression(CodeElement::EXP_VARIABLE_ID) {
	this->name = nullptr;
}

VariableIdentifier::~VariableIdentifier() {
	delete this->name;
}

void alinous::VariableIdentifier::preAnalyze(AnalyzeContext* actx) {

}

void alinous::VariableIdentifier::analyze(AnalyzeContext* actx) {

}

void VariableIdentifier::setName(UnicodeString* name) noexcept {
	this->name = name;
}

int VariableIdentifier::binarySize() const {
	checkNotNull(this->name);

	int total = sizeof(uint16_t);
	total += stringSize(this->name);

	return total;
}

void VariableIdentifier::toBinary(ByteBuffer* out) {
	checkNotNull(this->name);

	out->putShort(CodeElement::EXP_VARIABLE_ID);
	putString(out, this->name);
}

void VariableIdentifier::fromBinary(ByteBuffer* in) {
	this->name = getString(in);
}


AnalyzedType VariableIdentifier::getType() {
	// FIXME analyze variable id type
	return AnalyzedType();
}

} /* namespace alinous */
