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

void VariableDeclareStatement::preAnalyze(AnalyzeContext* actx) {
	this->type->setParent(this);
	this->variableId->setParent(this);
	this->variableId->preAnalyze(actx);
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void VariableDeclareStatement::analyzeTypeRef(AnalyzeContext* actx) {
	// FIXME analyzeTypeRef

	this->exp->analyzeTypeRef(actx);
}

void VariableDeclareStatement::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);
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

int VariableDeclareStatement::binarySize() const {
	checkNotNull(this->type);
	checkNotNull(this->variableId);
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->type->binarySize();
	total += this->variableId->binarySize();
	total += this->exp->binarySize();

	return total;
}

void VariableDeclareStatement::toBinary(ByteBuffer* out) {
	checkNotNull(this->type);
	checkNotNull(this->variableId);
	checkNotNull(this->exp);

	out->putShort(CodeElement::STMT_VARIABLE_DECLARE);
	this->type->toBinary(out);
	this->variableId->toBinary(out);
	this->exp->toBinary(out);
}

void VariableDeclareStatement::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsType(element);
	this->type = dynamic_cast<AbstractType*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::EXP_VARIABLE_ID);
	this->variableId = dynamic_cast<VariableIdentifier*>(element);

	element = createFromBinary(in);
	checkIsExp(element);
	this->exp = dynamic_cast<AbstractExpression*>(element);
}

void VariableDeclareStatement::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

void VariableDeclareStatement::interpret(VirtualMachine* vm) {
	// FIXME statement
}

} /* namespace alinous */
