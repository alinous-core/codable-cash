/*
 * ParenthesisScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_select/scan_columns_exp/ParenthesisScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

ParenthesisScanColumnTarget::ParenthesisScanColumnTarget() {
	this->cond = nullptr;
}

ParenthesisScanColumnTarget::~ParenthesisScanColumnTarget() {
	delete this->cond;
}

void ParenthesisScanColumnTarget::setInnser(AbstractScanColumnsTarget* cond) noexcept {
	this->cond = cond;
}

const UnicodeString* ParenthesisScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"(");

		this->str->append(this->cond->toStringCode());

		this->str->append(L")");
	}

	return this->str;
}

void ParenthesisScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->cond->resolveColumns(vm, planner);
}

} /* namespace codablecash */
