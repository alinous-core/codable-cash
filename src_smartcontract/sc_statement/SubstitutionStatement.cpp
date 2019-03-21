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

int SubstitutionStatement::binarySize() const {
	checkNotNull(this->variable);
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->variable->binarySize();
	total += this->exp->binarySize();

	return total;
}

void SubstitutionStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->variable);
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_SUBSTITUTION);
	this->variable->toBinary(out);
	this->exp->toBinary(out);
}

void SubstitutionStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_VARIABLE_ID);
	this->variable = dynamic_cast<VariableIdentifier*>(element);

	element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}


} /* namespace alinous */
