/*
 * ArrayReferenceAccess.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/ArrayReferenceAccess.h"

#include "sc_analyze/AnalyzedType.h"
#include "sc_analyze/AnalyzeContext.h"
#include "sc_analyze/ValidationError.h"

#include "sc_expression/ArrayReferenceExpression.h"

#include "instance_array/VmArrayInstanceUtils.h"


namespace alinous {

ArrayReferenceAccess::ArrayReferenceAccess(ArrayReferenceExpression* arrayRefExp)
				: AbstractVariableInstraction(AbstractVariableInstraction::INSTRUCTION_ARRAY_REF){
	this->arrayRefExp = arrayRefExp;
	this->expAccess = nullptr;
	this->atype = nullptr;
}

ArrayReferenceAccess::~ArrayReferenceAccess() {
	delete this->expAccess;
	delete this->atype;
}

void ArrayReferenceAccess::analyze(AnalyzeContext* actx, AbstractVariableInstraction* lastIinst, CodeElement* element) {
	this->expAccess->analyze(actx, lastIinst, element);

	AnalyzedType at = this->expAccess->getAnalyzedType();
	int dim = this->arrayRefExp->getDim();
	int previousDim = at.getDim();
	dim = previousDim - dim;

	if(dim < 0){
		actx->addValidationError(ValidationError::CODE_ARRAY_INDEX_OVERFLOW, element, L"Array dimension is too greater than the variable.", {});
		this->atype = new AnalyzedType();
		return;
	}

	at.setDim(dim);
	this->atype = new AnalyzedType(at);

	const ArrayList<AbstractExpression>* list = this->arrayRefExp->getIndexList();

	int maxLoop = list->size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractExpression* ex = list->get(i);
		ex->analyze(actx);

		AnalyzedType at = ex->getType(actx);
		bool res = VmArrayInstanceUtils::isArrayIndex(at);
		if(!res){
			actx->addValidationError(ValidationError::CODE_ARRAY_INDEX_MUST_BE_NUMERIC, element, L"Array index must be numeric value.", {});
		}
	}
}

AnalyzedType ArrayReferenceAccess::getAnalyzedType() const noexcept {
	return *this->atype;
}

AbstractVmInstance* ArrayReferenceAccess::interpret(VirtualMachine* vm, AbstractVmInstance* lastInst) {
	// FIXME interpret
	return nullptr;
}

CodeElement* ArrayReferenceAccess::getCodeElement() const noexcept {
	return this->arrayRefExp;
}

void ArrayReferenceAccess::setExpressionAccess(AbstractVariableInstraction* expAccess) noexcept {
	this->expAccess = expAccess;
}

} /* namespace alinous */
