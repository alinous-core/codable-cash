/*
 * ExpressionListScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_exp/ExpressionListScanColumnTarget.h"

#include "base/UnicodeString.h"

namespace codablecash {

ExpressionListScanColumnTarget::ExpressionListScanColumnTarget() {

}

ExpressionListScanColumnTarget::~ExpressionListScanColumnTarget() {
	this->list.deleteElements();
}

void ExpressionListScanColumnTarget::addElement(AbstractScanColumnsTarget* val) noexcept {
	this->list.addElement(val);
}

const UnicodeString* ExpressionListScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			AbstractScanColumnsTarget* vp = this->list.get(i);

			if(i > 0){
				this->str->append(L", ");
			}

			this->str->append(vp->toStringCode());
		}
	}

	return this->str;
}

void ExpressionListScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanColumnsTarget* vp = this->list.get(i);

		vp->resolveColumns(vm, planner);
	}
}


} /* namespace codablecash */
