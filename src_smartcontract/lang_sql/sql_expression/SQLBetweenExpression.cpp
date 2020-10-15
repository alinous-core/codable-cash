/*
 * SQLBetweenExpression.cpp
 *
 *  Created on: 2019/02/18
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLBetweenExpression.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "scan_select/scan_condition/exp/BetweenScanCondition.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_columns/scan_columns_exp/BetweenScanColumnTarget.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"


using codablecash::BetweenScanCondition;

namespace alinous {

SQLBetweenExpression::SQLBetweenExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_BETWEEN) {
	this->left = nullptr;
	this->start = nullptr;
	this->end = nullptr;
}

SQLBetweenExpression::~SQLBetweenExpression() {
	delete this->left;
	delete this->start;
	delete this->end;
}

void SQLBetweenExpression::setLeft(AbstractSQLExpression* exp) noexcept {
	this->left = exp;
}

void SQLBetweenExpression::setStart(AbstractSQLExpression* exp) noexcept {
	this->start = exp;
}

void SQLBetweenExpression::setEnd(AbstractSQLExpression* exp) noexcept {
	this->end = exp;
}

int SQLBetweenExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->start);
	checkNotNull(this->end);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->start->binarySize();
	total += this->end->binarySize();

	return total;
}

void SQLBetweenExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->start);
	checkNotNull(this->end);

	out->putShort(CodeElement::SQL_EXP_BETWEEN);
	this->left->toBinary(out);
	this->start->toBinary(out);
	this->end->toBinary(out);
}

void SQLBetweenExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->start = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkIsSQLExp(element);
	this->end = dynamic_cast<AbstractSQLExpression*>(element);
}

void SQLBetweenExpression::preAnalyze(AnalyzeContext* actx) {
	this->left->setParent(this);
	this->left->preAnalyze(actx);

	this->start->setParent(this);
	this->start->preAnalyze(actx);

	this->end->setParent(this);
	this->end->preAnalyze(actx);
}

void SQLBetweenExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->left->analyzeTypeRef(actx);
	this->start->analyzeTypeRef(actx);
	this->end->analyzeTypeRef(actx);
}

void SQLBetweenExpression::analyze(AnalyzeContext* actx) {
	this->left->analyze(actx);
	this->start->analyze(actx);
	this->end->analyze(actx);
}

AnalyzedType SQLBetweenExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLBetweenExpression::init(VirtualMachine* vm) {
	this->left->init(vm);
	this->start->init(vm);
	this->end->init(vm);
}

AbstractVmInstance* SQLBetweenExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	BetweenScanCondition* cond = new BetweenScanCondition();
	planner->push(cond);

	this->left->interpret(vm);
	this->start->interpret(vm);
	this->end->interpret(vm);

	AbstractScanConditionElement* element = nullptr;
	IValueProvider* val = nullptr;

	element = planner->pop();
	val = ScanConditionCast::toIValueProvider(element, vm, this);
	cond->setEnd(val);

	element = planner->pop();
	val = ScanConditionCast::toIValueProvider(element, vm, this);
	cond->setStart(val);

	element = planner->pop();
	val = ScanConditionCast::toIValueProvider(element, vm, this);
	cond->setLeft(val);

	return nullptr;
}

void SQLBetweenExpression::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	BetweenScanColumnTarget* cond = new BetweenScanColumnTarget();
	colHolder->push(cond);

	this->left->onSelectTarget(vm);
	this->start->onSelectTarget(vm);
	this->end->onSelectTarget(vm);

	AbstractScanColumnsTarget* col = nullptr;

	col = colHolder->pop();
	cond->setEnd(col);

	col = colHolder->pop();
	cond->setStart(col);

	col = colHolder->pop();
	cond->setLeft(col);
}

} /* namespace alinous */
