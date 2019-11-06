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

void MemberVariableAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst) {
	// FIXME analyze
}

AnalyzedType* MemberVariableAccess::getAnalyzedType() const noexcept {
	return nullptr; // FIXME
}

} /* namespace alinous */
