/*
 * ArrayReferenceAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/ArrayReferenceAccess.h"

namespace alinous {

ArrayReferenceAccess::ArrayReferenceAccess(ArrayReferenceExpression* arrayRefExp) {
	this->arrayRefExp = arrayRefExp;
}

ArrayReferenceAccess::~ArrayReferenceAccess() {
}

void ArrayReferenceAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst) {
}

AnalyzedType* ArrayReferenceAccess::getAnalyzedType() const noexcept {
	return nullptr; // FIXME
}

AbstractVmInstance* ArrayReferenceAccess::interpret(VirtualMachine* vm) {
	// FIXME interpret
	return nullptr;
}

} /* namespace alinous */
