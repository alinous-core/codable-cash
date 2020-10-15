/*
 * IsNullScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_select/scan_columns/scan_columns_exp/IsNullScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

IsNullScanColumnTarget::IsNullScanColumnTarget() {
	this->cond = nullptr;
	this->notnull = false;
}

IsNullScanColumnTarget::~IsNullScanColumnTarget() {
	delete this->cond;
}

void IsNullScanColumnTarget::setCondition(AbstractScanColumnsTarget* cond) noexcept {
	this->cond = cond;
}

void IsNullScanColumnTarget::setIsNull(bool notnull) noexcept {
	this->notnull = notnull;
}

const UnicodeString* IsNullScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		this->str->append(this->cond->toStringCode());

		this->str->append(L" IS");

		if(this->notnull){
			this->str->append(L" NOT");
		}

		this->str->append(L" NULL");
	}

	return this->str;
}

void IsNullScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->cond->resolveColumns(vm, planner);
}

} /* namespace codablecash */
