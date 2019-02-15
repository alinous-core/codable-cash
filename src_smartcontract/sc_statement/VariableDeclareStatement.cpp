/*
 * VariableDeclareStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement/VariableDeclareStatement.h"

#include "sc_declare_types/AbstractType.h"
#include "sc_expression/VariableIdentifier.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

VariableDeclareStatement::VariableDeclareStatement() : AbstractStatement(CodeElement::STMT_VARIABLE_DECLARE) {
	this->type =nullptr;
	this->variableId = nullptr;
	this->exp = nullptr;
}

VariableDeclareStatement::~VariableDeclareStatement() {
	delete this->type;
	delete this->variableId;
	delete this->exp;
}

void VariableDeclareStatement::setType(AbstractType* type) noexcept {
	this->type = type;
}

void VariableDeclareStatement::setVariableId(VariableIdentifier* variableId) noexcept {
	this->variableId = variableId;
}

void VariableDeclareStatement::setInitExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */
