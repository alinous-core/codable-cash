/*
 * ArrayReferenceAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/ArrayReferenceAccess.h"

#include "sc_analyze/AnalyzedType.h"

#include "sc_expression/ArrayReferenceExpression.h"

namespace alinous {

ArrayReferenceAccess::ArrayReferenceAccess(ArrayReferenceExpression* arrayRefExp) {
	this->arrayRefExp = arrayRefExp;
}

ArrayReferenceAccess::~ArrayReferenceAccess() {
}

void ArrayReferenceAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
}

AnalyzedType ArrayReferenceAccess::getAnalyzedType() const noexcept {
	return AnalyzedType(); // FIXME ArrayReferenceAccess
}

AbstractVmInstance* ArrayReferenceAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	// FIXME interpret
	return nullptr;
}

CodeElement* ArrayReferenceAccess::getCodeElement() const noexcept {
	return this->arrayRefExp;
}

} /* namespace alinous */
