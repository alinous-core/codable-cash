/*
 * RelationalScanCondition.cpp
 *
 *  Created on: 2020/07/29
 *      Author: iizuka
 */

#include "scan_select/scan_condition/exp/RelationalScanCondition.h"

#include "engine/sc/CodeElement.h"

#include "scan_select/scan_condition/base/IValueProvider.h"

#include "scan_select/scan_condition/params/ColumnIdentifierScanParam.h"

#include "engine/CdbException.h"

#include "base/UnicodeString.h"

#include "lang_sql/sql_expression/SQLRelationalExpression.h"

#include "scan_select/scan_planner/scanner/ctx/FilterConditionDitector.h"
#include "scan_select/scan_planner/scanner/ctx/FilterConditionStackMarker.h"

#include "scan_select/scan_planner/scanner/index/IndexCandidate.h"
#include "scan_select/scan_planner/scanner/index/TableIndexDetector.h"

#include "scan_select/scan_planner/base/SelectScanPlanner.h"

using namespace alinous;

namespace codablecash {

RelationalScanCondition::RelationalScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_RELATIONAL) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
	this->str = nullptr;
}

RelationalScanCondition::~RelationalScanCondition() {
	delete this->left;
	delete this->right;
	resetStr();
}

void RelationalScanCondition::setLeft(IValueProvider* element) {
	this->left = element;
	resetStr();
}

void RelationalScanCondition::setRight(IValueProvider* element) {
	this->right = element;
	resetStr();
}

void RelationalScanCondition::setOp(uint8_t op) noexcept {
	this->op = op;
}

const UnicodeString* RelationalScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		AbstractScanConditionElement* cond = dynamic_cast<AbstractScanConditionElement*>(this->left);
		this->str->append(cond->toStringCode());

		if(this->op == SQLRelationalExpression::GT){
			this->str->append(L" > ");
		}
		else if(this->op == SQLRelationalExpression::GT_EQ){
			this->str->append(L" >= ");
		}
		else if(this->op == SQLRelationalExpression::LT){
			this->str->append(L" < ");
		}
		else if(this->op == SQLRelationalExpression::LT_EQ){
			this->str->append(L" <= ");
		}

		cond = dynamic_cast<AbstractScanConditionElement*>(this->right);
		this->str->append(cond->toStringCode());
	}

	return this->str;
}

AbstractScanCondition* RelationalScanCondition::cloneCondition() const noexcept {
	RelationalScanCondition* cond = new RelationalScanCondition();

	cond->setLeft(this->left->clone());
	cond->setRight(this->right->clone());
	cond->setOp(this->op);

	return cond;
}

void RelationalScanCondition::detectFilterConditions(VirtualMachine* vm,
		SelectScanPlanner* planner, FilterConditionDitector* detector) {
	FilterConditionStackMarker marker(detector->getStack());

	if(this->left->isFilterable(vm, planner, detector) &&
			this->right->isFilterable(vm, planner, detector)){
		detector->push(cloneCondition());
	}
}

void RelationalScanCondition::detectIndexCondition(VirtualMachine* vm, SelectScanPlanner* planner,
		TableIndexDetector* detector) {
	ColumnIdentifierScanParam* column = nullptr;
	IValueProvider* value = nullptr;

	if(this->left->isColumn() && !this->right->isColumn()){
		column = dynamic_cast<ColumnIdentifierScanParam*>(this->left);
		value = this->right;
	}
	else if(!this->left->isColumn() && this->right->isColumn()){
		column = dynamic_cast<ColumnIdentifierScanParam*>(this->right);
		value = this->left;
	}
	else {
		return;
	}

	IndexCandidate* candidate = new IndexCandidate(IndexCandidate::IndexType::RANGE);
	candidate->setColumn(column);
	candidate->setValue(value);

	detector->push(candidate);
}

void RelationalScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void RelationalScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->analyzeConditions(vm, planner);
	this->right->analyzeConditions(vm, planner);
}

} /* namespace codablecash */
