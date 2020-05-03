/*
 * AbstractExpression.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_expression/AbstractExpression.h"

#include "variable_access/VariableInstractionHolder.h"

#include "sc_declare/MethodDeclare.h"
#include "sc_declare/MemberVariableDeclare.h"

#include "sc_expression/ConstructorCall.h"


namespace alinous {

AbstractExpression::AbstractExpression(int kind) : CodeElement(kind) {
	this->valInstHolder = nullptr;
	this->exceptionThorown = false;
}

AbstractExpression::~AbstractExpression() {
	delete this->valInstHolder;
}

bool AbstractExpression::isStaticMode() noexcept {
	bool mode = false;
	CodeElement* element = this;

	while(element != nullptr){
		short elementKind = element->getKind();

		if(elementKind == CodeElement::METHOD_DECLARE){
			MethodDeclare* method = dynamic_cast<MethodDeclare*>(element);
			mode = method->isStatic();
			break;
		}
		else if(elementKind == CodeElement::MEMBER_VARIABLE_DECLARE){
			MemberVariableDeclare* member = dynamic_cast<MemberVariableDeclare*>(element);
			mode = member->isStatic();
			break;
		}

		element = element->getParent();
	}

	return mode;
}

VariableInstractionHolder* AbstractExpression::getVariableInstractionHolder() noexcept {
	if(this->valInstHolder == nullptr){
		this->valInstHolder = new VariableInstractionHolder();
	}
	return this->valInstHolder;
}

bool AbstractExpression::isExecutable() {
	return true;
}

bool AbstractExpression::throwsException() const noexcept {
	return this->exceptionThorown;
}

void AbstractExpression::setThrowsException(bool exThrow) noexcept {
	this->exceptionThorown = exThrow;
}

} /* namespace alinous */
