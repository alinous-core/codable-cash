/*
 * SQLInExpression.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "sql_expression/SQLInExpression.h"
#include "sql_expression/SQLExpressionList.h"

#include "sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_planner/SelectScanPlanner.h"

#include "scan_condition_exp/InExpressionScanCondition.h"

#include "scan_condition/ScanConditionCast.h"

using codablecash::ScanConditionCast;

namespace alinous {

SQLInExpression::SQLInExpression() : AbstractSQLExpression(CodeElement::SQL_EXP_IN) {
	this->left = nullptr;
	this->list = nullptr;
}

SQLInExpression::~SQLInExpression() {
	delete this->left;
	delete this->list;
}

void SQLInExpression::setLeft(AbstractSQLExpression* left) noexcept {
	this->left = left;
}

void SQLInExpression::setList(SQLExpressionList* list) noexcept {
	this->list = list;
}

int SQLInExpression::binarySize() const {
	checkNotNull(this->left);
	checkNotNull(this->list);

	int total = sizeof(uint16_t);
	total += this->left->binarySize();
	total += this->list->binarySize();

	return total;
}

void SQLInExpression::toBinary(ByteBuffer* out) {
	checkNotNull(this->left);
	checkNotNull(this->list);

	out->putShort(CodeElement::SQL_EXP_IN);
	this->left->toBinary(out);
	this->list->toBinary(out);
}

void SQLInExpression::fromBinary(ByteBuffer* in) {
	CodeElement* element = createFromBinary(in);
	checkIsSQLExp(element);
	this->left = dynamic_cast<AbstractSQLExpression*>(element);

	element = createFromBinary(in);
	checkKind(element, CodeElement::SQL_EXP_EXP_LIST);
	this->list = dynamic_cast<SQLExpressionList*>(element);
}

void SQLInExpression::preAnalyze(AnalyzeContext* actx) {
	this->left->setParent(this);
	this->left->preAnalyze(actx);

	this->list->setParent(this);
	this->list->preAnalyze(actx);
}

void SQLInExpression::analyzeTypeRef(AnalyzeContext* actx) {
	this->left->analyzeTypeRef(actx);
	this->list->analyzeTypeRef(actx);
}

void SQLInExpression::analyze(AnalyzeContext* actx) {
	this->left->analyze(actx);
	this->list->analyze(actx);
}

AnalyzedType SQLInExpression::getType(AnalyzeContext* actx) {
	return AnalyzedType(AnalyzedType::TYPE_BOOL);
}

void SQLInExpression::init(VirtualMachine* vm) {
	this->left->init(vm);
	this->list->init(vm);
}

AbstractVmInstance* SQLInExpression::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();

	InExpressionScanCondition* cond = new InExpressionScanCondition();
	planner->push(cond);

	AbstractScanConditionElement* element = nullptr;
	IValueProvider* val = nullptr;

	this->left->interpret(vm);
	element = planner->pop();
	val = ScanConditionCast::toIValueProvider(element, vm, this);

	cond->setLeft(val);

	this->list->interpret(vm);
	element = planner->pop();
	ExpressionListScanCondition* l = ScanConditionCast::toExpressionList(element, vm, this);

	cond->setList(l);

	return nullptr;
}


} /* namespace alinous */
