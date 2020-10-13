/*
 * StaticVariableMetadata.cpp
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#include "instance/instance_ref_class_static_meta/StaticVariableMetadata.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "lang/sc_declare/MemberVariableDeclare.h"

namespace alinous {

StaticVariableMetadata::StaticVariableMetadata(int index, MemberVariableDeclare* val, StaticClassMetadata* parent) {
	this->index = index;
	this->val = val;
	this->parent = parent;
}

StaticVariableMetadata::~StaticVariableMetadata() {
	this->val = nullptr;
}

AnalyzedType StaticVariableMetadata::getAnalyzedType() const noexcept {
	return this->val->getAnalyzedType();
}

int StaticVariableMetadata::getIndex() const noexcept {
	return this->index;
}

StaticClassMetadata* StaticVariableMetadata::getParent() const noexcept {
	return this->parent;
}

} /* namespace alinous */
