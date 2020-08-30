/*
 * MultiplicativeScanCondition.cpp
 *
 *  Created on: 2020/08/04
 *      Author: iizuka
 */

#include "scan_condition_arithmetic/MultiplicativeScanCondition.h"

#include "sc/CodeElement.h"

#include "base/UnicodeString.h"

#include "sql_expression/SqlMultiplicativeExpression.h"
namespace codablecash {

MultiplicativeScanCondition::MultiplicativeScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_MULTIPLICATIVE), operations(2){
	this->str = nullptr;
}

MultiplicativeScanCondition::~MultiplicativeScanCondition() {
	this->list.deleteElements();
	resetStr();
}

const UnicodeString* MultiplicativeScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
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

			IValueProvider* vp = this->list.get(i);
			AbstractScanConditionElement* el = dynamic_cast<AbstractScanConditionElement*>(vp);

			this->str->append(el->toStringCode());
		}

	}

	return this->str;
}

void MultiplicativeScanCondition::addOperand(IValueProvider* vp) noexcept {
	this->list.addElement(vp);
	resetStr();
}

void MultiplicativeScanCondition::addOperator(uint8_t op) noexcept {
	this->operations.addElement(op);
	resetStr();
}

void MultiplicativeScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

void MultiplicativeScanCondition::analyzeConditions(VirtualMachine* vm, SelectScanPlanner* planner) {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		IValueProvider* vp = this->list.get(i);

		vp->analyzeConditions(vm, planner);
	}
}


} /* namespace codablecash */
