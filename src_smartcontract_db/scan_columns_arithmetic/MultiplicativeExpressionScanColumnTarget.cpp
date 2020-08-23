/*
 * MultiplicativeExpressionScanColumnTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_columns_arithmetic/MultiplicativeExpressionScanColumnTarget.h"

#include "base/UnicodeString.h"

#include "sql_expression/SqlMultiplicativeExpression.h"

namespace codablecash {

MultiplicativeExpressionScanColumnTarget::MultiplicativeExpressionScanColumnTarget() : operations(2) {

}

MultiplicativeExpressionScanColumnTarget::~MultiplicativeExpressionScanColumnTarget() {
	this->list.deleteElements();
}

void MultiplicativeExpressionScanColumnTarget::addOperand(AbstractScanColumnsTarget* vp) noexcept {
	this->list.addElement(vp);
}

void MultiplicativeExpressionScanColumnTarget::addOperator(uint8_t op) noexcept {
	this->operations.addElement(op);
}

const UnicodeString* MultiplicativeExpressionScanColumnTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		int maxLoop = this->list.size();
		for(int i = 0; i != maxLoop; ++i){
			if(i > 0){
				int pos = i - 1;
				uint8_t op = this->operations.get(pos);

				if(op == SqlMultiplicativeExpression::MUL){
					this->str->append(L" * ");
				}
				else if(op == SqlMultiplicativeExpression::DIV){
					this->str->append(L" / ");
				}
				else if(op == SqlMultiplicativeExpression::MOD){
					this->str->append(L" % ");
				}
			}

			AbstractScanColumnsTarget* vp = this->list.get(i);

			this->str->append(vp->toStringCode());
		}
	}

	return this->str;
}

} /* namespace codablecash */
