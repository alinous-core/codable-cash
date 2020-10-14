/*
 * SQLExpressionList.cpp
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#include "lang_sql/sql_expression/SQLExpressionList.h"

#include "engine/sc_analyze/AnalyzedType.h"

#include "vm/VirtualMachine.h"

#include "scan_select/scan_condition/exp/ExpressionListScanCondition.h"
#include "scan_select/scan_condition/base/IValueProvider.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"
#include "scan_select/scan_planner/base/ConditionsHolderStackMarker.h"

#include "scan_select/scan_condition/base/ScanConditionCast.h"

#include "scan_select/scan_columns/ScanColumnHolder.h"

#include "scan_select/scan_columns/scan_columns_exp/ExpressionListScanColumnTarget.h"


namespace alinous {

SQLExpressionList::SQLExpressionList() : AbstractSQLExpression(CodeElement::SQL_EXP_EXP_LIST) {
}

SQLExpressionList::~SQLExpressionList() {
	this->list.deleteElements();
}

void SQLExpressionList::addExpression(AbstractSQLExpression* exp) noexcept {
	this->list.addElement(exp);
}

AbstractSQLExpression* SQLExpressionList::getExpression(int i) const noexcept {
	return this->list.get(i);
}

int SQLExpressionList::binarySize() const {
	int total = sizeof(uint16_t);

	total += sizeof(uint32_t);
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);
		total += exp->binarySize();
	}

	return total;
}

void SQLExpressionList::toBinary(ByteBuffer* out) {
	out->putShort(CodeElement::SQL_EXP_EXP_LIST);

	int maxLoop = this->list.size();
	out->putInt(maxLoop);

	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);
		exp->toBinary(out);
	}
}

void SQLExpressionList::fromBinary(ByteBuffer* in) {
	int maxLoop = in->getInt();
	for(int i = 0; i != maxLoop; ++i){
		CodeElement* element = createFromBinary(in);
		checkIsSQLExp(element);
		AbstractSQLExpression* exp = dynamic_cast<AbstractSQLExpression*>(element);

		this->list.addElement(exp);
	}
}

void SQLExpressionList::preAnalyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->setParent(this);
		exp->preAnalyze(actx);
	}
}

void SQLExpressionList::analyzeTypeRef(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->analyzeTypeRef(actx);
	}
}

void SQLExpressionList::analyze(AnalyzeContext* actx) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->analyze(actx);
	}
}

AnalyzedType SQLExpressionList::getType(AnalyzeContext* actx) {
	return AnalyzedType();
}

void SQLExpressionList::init(VirtualMachine* vm) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->init(vm);
	}
}

int SQLExpressionList::numExpressions() const noexcept {
	return this->list.size();
}

AbstractVmInstance* SQLExpressionList::interpret(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ConditionsHolderStackMarker marker(planner->getConditionsStack());

	ExpressionListScanCondition* cond = new ExpressionListScanCondition();
	planner->push(cond);

	AbstractScanConditionElement* element = nullptr;
	IValueProvider* val = nullptr;

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->interpret(vm);
		element = planner->pop();
		val = ScanConditionCast::toIValueProvider(element, vm, this);

		cond->addElement(val);
	}

	return nullptr;
}

void SQLExpressionList::onSelectTarget(VirtualMachine* vm) {
	SelectScanPlanner* planner = vm->getSelectPlanner();
	ScanColumnHolder* colHolder = planner->getColumnHolder();

	ExpressionListScanColumnTarget* cond = new ExpressionListScanColumnTarget();
	colHolder->push(cond);

	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractSQLExpression* exp = this->list.get(i);

		exp->onSelectTarget(vm);

		AbstractScanColumnsTarget* col = colHolder->pop();
		cond->addElement(col);
	}
}

} /* namespace alinous */
