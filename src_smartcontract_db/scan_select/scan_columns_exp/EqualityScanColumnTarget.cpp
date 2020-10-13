/*
 * EqualityScanColumnTarget.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_select/scan_columns_exp/EqualityScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

EqualityScanColumnTarget::EqualityScanColumnTarget() {
	this->left = nullptr;
	this->right = nullptr;
}

EqualityScanColumnTarget::~EqualityScanColumnTarget() {
	delete this->left;
	delete this->right;
}

void EqualityScanColumnTarget::setLeft(AbstractScanColumnsTarget* element) noexcept {
	this->left = element;
}

void EqualityScanColumnTarget::setRight(AbstractScanColumnsTarget* element) noexcept {
	this->right = element;
}

const UnicodeString* EqualityScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toStringCode());

		this->str->append(L" = ");

		this->str->append(this->right->toStringCode());
	}

	return this->str;
}

void EqualityScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->resolveColumns(vm, planner);
	this->right->resolveColumns(vm, planner);
}


} /* namespace codablecash */
