/*
 * OrlScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_logical/OrScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

OrScanColumnTarget::OrScanColumnTarget() {

}

OrScanColumnTarget::~OrScanColumnTarget() {
	this->list.deleteElements();
}

void OrScanColumnTarget::addCondition(AbstractScanColumnsTarget* cond) noexcept {
	this->list.addElement(cond);
}

const UnicodeString* OrScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanColumnsTarget* cond = this->list.get(i);

			if(i != 0){
				this->str->append(L" OR ");
			}

			this->str->append(cond->toStringCode());
		}
	}

	return this->str;
}

void OrScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanColumnsTarget* cond = this->list.get(i);

		cond->resolveColumns(vm, planner);
	}
}

} /* namespace codablecash */
