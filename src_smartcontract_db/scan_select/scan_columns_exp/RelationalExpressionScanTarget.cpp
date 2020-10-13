/*
 * RelationalExpressionScanTarget.cpp
 *
 *  Created on: 2020/08/21
 *      Author: iizuka
 */

#include "scan_select/scan_columns_exp/RelationalExpressionScanTarget.h"

#include "base/UnicodeString.h"

#include "lang_sql/sql_expression/SQLRelationalExpression.h"

namespace codablecash {

RelationalExpressionScanTarget::RelationalExpressionScanTarget() {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

RelationalExpressionScanTarget::~RelationalExpressionScanTarget() {
	delete this->left;
	delete this->right;
}

void RelationalExpressionScanTarget::setLeft(AbstractScanColumnsTarget* element) noexcept {
	this->left = element;
}

void RelationalExpressionScanTarget::setRight(AbstractScanColumnsTarget* element) noexcept {
	this->right = element;
}

void RelationalExpressionScanTarget::setOp(uint8_t op) noexcept {
	this->op = op;
}

const UnicodeString* RelationalExpressionScanTarget::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"");

		this->str->append(this->left->toStringCode());

		if(this->op == SQLRelationalExpression::GT){
			this->str->append(L" > ");
		}
		else if(this->op == SQLRelationalExpression::GT_EQ){
			this->str->append(L" >= ");
		}
		else if(this->op == SQLRelationalExpression::LT){
			this->str->append(L" < ");
		}
		else if(this->op == SQLRelationalExpression::LT_EQ){
			this->str->append(L" <= ");
		}

		this->str->append(this->right->toStringCode());
	}

	return this->str;
}

void RelationalExpressionScanTarget::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {
	this->left->resolveColumns(vm, planner);
	this->right->resolveColumns(vm, planner);
}


} /* namespace codablecash */
