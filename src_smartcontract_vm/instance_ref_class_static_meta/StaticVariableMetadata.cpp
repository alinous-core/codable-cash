/*
 * StaticVariableMetadata.cpp
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#include "instance_ref_class_static_meta/StaticVariableMetadata.h"

#include "sc_analyze/AnalyzedType.h"

#include "sc_declare/MemberVariableDeclare.h"

namespace alinous {

StaticVariableMetadata::StaticVariableMetadata(int index, MemberVariableDeclare* val) {
	this->index = index;
	this->val = val;
}

StaticVariableMetadata::~StaticVariableMetadata() {
	this->val = nullptr;
}

AnalyzedType StaticVariableMetadata::getAnalyzedType() const noexcept {
	return this->val->getAnalyzedType();
}

} /* namespace alinous */
