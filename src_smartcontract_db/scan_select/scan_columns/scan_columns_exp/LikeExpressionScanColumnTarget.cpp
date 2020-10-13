/*
 * LikeExpression.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_select/scan_columns/scan_columns_exp/LikeExpressionScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

LikeExpressionScanColumnTarget::LikeExpressionScanColumnTarget() {
	this->left = nullptr;
	this->right = nullptr;
	this->escape = nullptr;
}

LikeExpressionScanColumnTarget::~LikeExpressionScanColumnTarget() {
	delete this->left;
	delete this->right;
	delete this->escape;
}

void LikeExpressionScanColumnTarget::setLeft(AbstractScanColumnsTarget* left) noexcept {
	this->left = left;
}

void LikeExpressionScanColumnTarget::setRight(AbstractScanColumnsTarget* right) noexcept {
	this->right = right;
}

void LikeExpressionScanColumnTarget::setEscape(AbstractScanColumnsTarget* escape) noexcept {
	this->escape = escape;
}

const UnicodeString* LikeExpressionScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toStringCode());

		this->str->append(L" LIKE ");

		this->str->append(this->right->toStringCode());

		if(this->escape != nullptr){
			this->str->append(L" ESCAPE ");
			this->str->append(this->escape->toStringCode());
		}
	}

	return this->str;
}

void LikeExpressionScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->resolveColumns(vm, planner);
	this->right->resolveColumns(vm, planner);

	if(this->escape != nullptr){
		this->escape->resolveColumns(vm, planner);
	}
}

} /* namespace codablecash */
