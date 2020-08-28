/*
 * AndLogicalScanColumn.cpp
 *
 *  Created on: 2020/08/20
 *      Author: iizuka
 */

#include "scan_columns_logical/AndScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

AndScanColumnTarget::AndScanColumnTarget() {

}

AndScanColumnTarget::~AndScanColumnTarget() {
	this->list.deleteElements();
}

void AndScanColumnTarget::addCondition(AbstractScanColumnsTarget* cond) noexcept {
	this->list.addElement(cond);
}

const UnicodeString* AndScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanColumnsTarget* cond = this->list.get(i);

			if(i != 0){
				this->str->append(L" AND ");
			}

			this->str->append(cond->toStringCode());
		}
	}

	return this->str;
}

void AndScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanColumnsTarget* cond = this->list.get(i);

		cond->resolveColumns(vm, planner);
	}
}


} /* namespace codablecash */
