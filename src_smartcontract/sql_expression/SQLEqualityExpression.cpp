/*
 * SQLEqualityExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLEqualityExpression.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_planner/SelectScanPlanner.h"
#include "scan_planner/ConditionStackPopper.h"

#include "scan_condition/AbstractScanCondition.h"
#include "scan_condition/EqualityScanCondition.h"


namespace alinous {

SQLEqualityExpression::SQLEqualityExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_EQUALITY) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

SQLEqualityExpression::~SQLEqualityExpression() {
	delete this->left;
	delete this->right;
}

void SQLEqualityExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLEqualityExpression::setRight(AbstractSQLExpression* exp) noexcept {
	this->right = exp;
}

void SQLEqualityExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

int SQLEqualityExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->right);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->right->binarySize();
	total += sizeof(uint8_t);

	return total;
}

void SQLEqualityExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->right);

	out->putShort(CodeElement::SQL_EXP_EQUALITY);
	this->left->toBinary(out);
	this->right->toBinary(out);
	out->put(this->op);
}

void SQLEqualityExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->right = dynamic_cast<AbstractSQLExpression*>(element);

	this->op = in->get();
}

void SQLEqualityExpression::preAnalyze(AnalyzeContext* actx) {
	this->left->setParent(this);
	this->left->preAnalyze(actx);

	this->right->setParent(this);
	this->right->preAnalyze(actx);
}

void SQLEqualityExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->left->analyzeTypeRef(actx);
	this->right->analyzeTypeRef(actx);
}

void SQLEqualityExpression::analyze(AnalyzeContext* actx) {
	this->left->analyze(actx);
	this->right->analyze(actx);
}

AnalyzedType SQLEqualityExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLEqualityExpression::init(VirtualMachine* vm) {
	this->left->init(vm);
	this->right->init(vm);
}

AbstractVmInstance* SQLEqualityExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();

	EqualityScanCondition* cond = new EqualityScanCondition();
	planner->processExpression(cond);
	ConditionStackPopper popper(planner);

	this->left->interpret(vm);
	this->right->interpret(vm);

	// FIXME set equality params

	return nullptr;
}


} /* namespace alinous */
