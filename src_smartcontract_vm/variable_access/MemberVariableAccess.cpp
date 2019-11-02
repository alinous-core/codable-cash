/*
 * MemberVariableAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/MemberVariableAccess.h"

namespace alinous {

MemberVariableAccess::MemberVariableAccess(VariableIdentifier* valId) {
	this->valId = valId;
}

MemberVariableAccess::~MemberVariableAccess() {
}

} /* namespace alinous */
