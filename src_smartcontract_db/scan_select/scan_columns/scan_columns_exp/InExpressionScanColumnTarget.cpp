/*
 * InExpressionScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_select/scan_columns/scan_columns_exp/InExpressionScanColumnTarget.h"

#include "scan_select/scan_columns/scan_columns_exp/ExpressionListScanColumnTarget.h"

#include "instance/instance_exception/TypeCastExceptionClassDeclare.h"
#include "instance/instance_exception/ExceptionInterrupt.h"

#include "base/UnicodeString.h"

#include "engine/CdbException.h"
namespace codablecash {

InExpressionScanColumnTarget::InExpressionScanColumnTarget() {
	this->left = nullptr;
	this->list = nullptr;
}

InExpressionScanColumnTarget::~InExpressionScanColumnTarget() {
	delete this->left;
	delete this->list;
}

void InExpressionScanColumnTarget::setLeft(AbstractScanColumnsTarget* cond) noexcept {
	this->left = cond;
}

void InExpressionScanColumnTarget::setList(ExpressionListScanColumnTarget* list) noexcept {
	this->list = list;
}

ExpressionListScanColumnTarget* InExpressionScanColumnTarget::castToExpressionListScanColumnTarget(AbstractScanColumnsTarget* col, VirtualMachine* vm, const CodeElement* element) {
	ExpressionListScanColumnTarget* val = dynamic_cast<ExpressionListScanColumnTarget*>(col);

	if(val == nullptr){
		delete col;

		throw new CdbException(__FILE__, __LINE__);
	}

	return val;
}

const UnicodeString* InExpressionScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toStringCode());
		this->str->append(L" IN (");

		this->str->append(this->list->toStringCode());
		this->str->append(L")");
	}

	return this->str;
}

void InExpressionScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->resolveColumns(vm, planner);
	this->list->resolveColumns(vm, planner);
}


} /* namespace codablecash */
