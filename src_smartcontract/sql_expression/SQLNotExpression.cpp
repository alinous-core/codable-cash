/*
 * SQLNotExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLNotExpression.h"

#include "sc_analyze/AnalyzedType.h"

#include "instance_gc/StackFloatingVariableHandler.h"

#include "vm/VirtualMachine.h"

#include "instance_ref/PrimitiveReference.h"

#include "sc_analyze/ValidationError.h"
#include "sc_analyze/AnalyzeContext.h"

namespace alinous {

SQLNotExpression::SQLNotExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_NOT) {
	this->exp = nullptr;
}

SQLNotExpression::~SQLNotExpression() {
	delete this->exp;
}

void SQLNotExpression::setExpression(AbstractSQLExpression* exp) noexcept {
	this->exp = exp;
}

int SQLNotExpression::binarySize() const {
	checkNotNull(this->exp);

	int total = sizeof(uint16_t);
	total += this->exp->binarySize();

	return total;
}

void SQLNotExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->exp);

	out->putShort(CodeElement::SQL_EXP_NOT);
	this->exp->toBinary(out);
}

void SQLNotExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->exp = dynamic_cast<AbstractSQLExpression*>(element);
}

void SQLNotExpression::preAnalyze(AnalyzeContext* actx) {
	this->exp->setParent(this);
	this->exp->preAnalyze(actx);
}

void SQLNotExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->exp->analyzeTypeRef(actx);
}

void SQLNotExpression::analyze(AnalyzeContext* actx) {
	this->exp->analyze(actx);

	AnalyzedType at = this->exp->getType(actx);
	if(!at.isBool()){
		actx->addValidationError(ValidationError::CODE_LOGICAL_EXP_NON_BOOL, this, L"Not expression requires boolean value.", {});
	}
}

AnalyzedType SQLNotExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLNotExpression::init(VirtualMachine* vm) {
	this->exp->init(vm);
}

AbstractVmInstance* SQLNotExpression::interpret(VirtualMachine* vm) {
	StackFloatingVariableHandler releaser(vm->getGc());

	AbstractVmInstance* inst = this->exp->interpret(vm);
	releaser.registerInstance(inst);

	PrimitiveReference* ref = dynamic_cast<PrimitiveReference*>(inst);
	bool bl = ref->getBoolValue();

	return PrimitiveReference::createBoolReference(vm, bl ? 0 : 1);
}


} /* namespace alinous */
