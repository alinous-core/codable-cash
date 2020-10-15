/*
 * SQLRelationalExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLRelationalExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_condition/exp/RelationalScanCondition.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_exp/RelationalExpressionScanTarget.h"


using namespace codablecash;

namespace alinous {

SQLRelationalExpression::SQLRelationalExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_RELATIONAL) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

SQLRelationalExpression::~SQLRelationalExpression() {
	delete this->left;
	delete this->right;
}

void SQLRelationalExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLRelationalExpression::setRight(AbstractSQLExpression* exp) noexcept {
	this->right = exp;
}

void SQLRelationalExpression::setOp(uint8_t op) noexcept {
	this->op = op;
}

int SQLRelationalExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->right);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->right->binarySize();
	total += sizeof(uint8_t);

	return total;
}

void SQLRelationalExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->right);

	out->putShort(CodeElement::SQL_EXP_RELATIONAL);
	this->left->toBinary(out);
	this->right->toBinary(out);
	out->put(this->op);
}

void SQLRelationalExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->right = dynamic_cast<AbstractSQLExpression*>(element);

	this->op = in->get();
}

void SQLRelationalExpression::preAnalyze(AnalyzeContext* actx) {
	this->left->setParent(this);
	this->left->preAnalyze(actx);

	this->right->setParent(this);
	this->right->preAnalyze(actx);
}

void SQLRelationalExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->left->analyzeTypeRef(actx);
	this->right->analyzeTypeRef(actx);
}

void SQLRelationalExpression::analyze(AnalyzeContext* actx) {
	this->left->analyze(actx);
	this->right->analyze(actx);
}

AnalyzedType SQLRelationalExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLRelationalExpression::init(VirtualMachine* vm) {
	this->left->init(vm);
	this->right->init(vm);
}

AbstractVmInstance* SQLRelationalExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	RelationalScanCondition* cond = new RelationalScanCondition();
	planner->push(cond);

	this->left->interpret(vm);
	this->right->interpret(vm);


	AbstractScanConditionElement* element = nullptr;
	IValueProvider* val = nullptr;

	cond->setOp(this->op);

	element = planner->pop();
	val = ScanConditionCast::toIValueProvider(element, vm, this);
	cond->setRight(val);

	element = planner->pop();
	val = ScanConditionCast::toIValueProvider(element, vm, this);
	cond->setLeft(val);

	return nullptr;
}

void SQLRelationalExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	RelationalExpressionScanTarget* cond = new RelationalExpressionScanTarget();
	colHolder->push(cond);

	this->left->onSelectTarget(vm);
	this->right->onSelectTarget(vm);

	cond->setOp(this->op);

	AbstractScanColumnsTarget* col = colHolder->pop();
	cond->setRight(col);

	col = colHolder->pop();
	cond->setLeft(col);
}

} /* namespace alinous */
