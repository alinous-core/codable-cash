/*
 * VariableInstractionHolder.cpp
 *
 *  Created on: 2019/10/31
 *      Author: iizuka
 */

#include "variable_access/VariableInstractionHolder.h"

#include "variable_access/AbstractVariableInstraction.h"

#include "sc_expression/AbstractExpression.h"
#include "sc_expression/VariableIdentifier.h"

#include "sc_analyze/AnalyzeContext.h"

#include "variable_access/ExpressionAccess.h"
#include "variable_access/ThisPointerAccess.h"

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

} /* namespace alinous */
