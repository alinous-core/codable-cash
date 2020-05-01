/*
 * StaticVariableMetadata.cpp
 *
 *  Created on: 2020/04/30
 *      Author: iizuka
 */

#include "instance_ref_class_static_meta/StaticVariableMetadata.h"

namespace alinous {

StaticVariableMetadata::StaticVariableMetadata(int index, MemberVariableDeclare* val) {
	this->index = index;
	this->val = val;
}

StaticVariableMetadata::~StaticVariableMetadata() {
	this->val = nullptr;
}

} /* namespace alinous */
