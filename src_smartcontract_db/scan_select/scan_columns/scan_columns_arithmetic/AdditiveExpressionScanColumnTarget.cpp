/*
 * AdditiveExpressionScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_select/scan_columns_arithmetic/AdditiveExpressionScanColumnTarget.h"

#include "base/UnicodeString.h"

#include "lang_sql/sql_expression/SQLAdditiveExpression.h"

namespace codablecash {

AdditiveExpressionScanColumnTarget::AdditiveExpressionScanColumnTarget() : operations(2) {

}

AdditiveExpressionScanColumnTarget::~AdditiveExpressionScanColumnTarget() {
	this->list.deleteElements();

}

void AdditiveExpressionScanColumnTarget::addOperand(AbstractScanColumnsTarget* vp) noexcept {
	this->list.addElement(vp);
}

void AdditiveExpressionScanColumnTarget::addOperator(uint8_t op) noexcept {
	this->operations.addElement(op);
}

const UnicodeString* AdditiveExpressionScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			if(i > 0){
				int pos = i - 1;
				uint8_t op = this->operations.get(pos);

				if(op == SQLAdditiveExpression::ADD){
					this->str->append(L" + ");
				}
				else if(op == SQLAdditiveExpression::SUB){
					this->str->append(L" - ");
				}
			}

			AbstractScanColumnsTarget* vp = this->list.get(i);

			this->str->append(vp->toStringCode());
		}
	}

	return this->str;
}

void AdditiveExpressionScanColumnTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AbstractScanColumnsTarget* vp = this->list.get(i);
		vp->resolveColumns(vm, planner);
	}
}


} /* namespace codablecash */
