/*
 * VariableInstractionHolder.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/VariableInstractionHolder.h"

#include "sc_expression/AbstractExpression.h"
#include "sc_expression/VariableIdentifier.h"
#include "sc_expression/ArrayReferenceExpression.h"

#include "sc_analyze/AnalyzeContext.h"

#include "variable_access/AbstractVariableInstraction.h"
#include "variable_access/ExpressionAccess.h"
#include "variable_access/ThisPointerAccess.h"
#include "variable_access/ArrayReferenceAccess.h"


namespace alinous {

VariableInstractionHolder::VariableInstractionHolder() {
	this->memberAccess = false;
}

VariableInstractionHolder::~VariableInstractionHolder() {
	this->list.deleteElements();
}

void VariableInstractionHolder::addExpression(AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	short kind = exp->getKind();

	switch(kind){
	case CodeElement::EXP_VARIABLE_ID:
		addVariableIdExp(exp, actx);
		break;
	case CodeElement::EXP_ARRAY_REF:
		addArrayReference(exp, actx);
		break;
	default:
		ExpressionAccess* access = new ExpressionAccess(exp);
		this->list.addElement(access);
		break;
	}
}

void VariableInstractionHolder::addVariableIdExp(AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	VariableIdentifier* valId = dynamic_cast<VariableIdentifier*>(exp);
	assert(valId != nullptr);

	if(valId->isThis()){
		if(this->list.isEmpty()){
			ThisPointerAccess* access = new ThisPointerAccess();
			this->list.addElement(access);
			this->memberAccess = true;
		}
		return;
	}

	// stack or not
	if(!this->memberAccess){
		// FIXME stack
	}

	// member access
	if(this->list.isEmpty()){
		ThisPointerAccess* access = new ThisPointerAccess();
		this->list.addElement(access);
		this->memberAccess = true;
	}



}

void VariableInstractionHolder::addArrayReference(AbstractExpression* exp, AnalyzeContext* actx) noexcept {
	ArrayReferenceExpression* arrayRefExp = dynamic_cast<ArrayReferenceExpression*>(exp);
	assert(arrayRefExp != nullptr);

	// FIXME array is stack object or

	ArrayReferenceAccess* access = new ArrayReferenceAccess(arrayRefExp);
	this->list.addElement(access);
}

} /* namespace alinous */
