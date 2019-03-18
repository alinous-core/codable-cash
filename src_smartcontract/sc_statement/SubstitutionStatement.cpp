/*
 * SubstitutionStatement.cpp
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#include "sc_statement/SubstitutionStatement.h"
#include "sc_expression/VariableIdentifier.h"
#include "sc_expression/AbstractExpression.h"

namespace alinous {

SubstitutionStatement::SubstitutionStatement() : AbstractStatement(CodeElement::STMT_SUBSTITUTION) {
	this->variable = nullptr;
	this->exp = nullptr;
}

SubstitutionStatement::~SubstitutionStatement() {
	delete this->variable;
	delete this->exp;
}

void SubstitutionStatement::setVariableId(VariableIdentifier* variable) noexcept {
	this->variable = variable;
}

void SubstitutionStatement::setExpression(AbstractExpression* exp) noexcept {
	this->exp = exp;
}

} /* namespace alinous */

int alinous::SubstitutionStatement::binarySize() const {
}

void alinous::SubstitutionStatement::toBinary(ByteBuffer* out) {
}

void alinous::SubstitutionStatement::fromBinary(ByteBuffer* in) {
}
