/*
 * RelationalScanCondition.cpp
 *
 *  Created on: 2020/07/29
 *      Author: iizuka
 */

#include "scan_condition_exp/RelationalScanCondition.h"

#include "sc/CodeElement.h"

#include "scan_condition/IValueProvider.h"

#include "engine/CdbException.h"

#include "base/UnicodeString.h"

#include "sql_expression/SQLRelationalExpression.h"

using namespace alinous;

namespace codablecash {

RelationalScanCondition::RelationalScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_RELATIONAL) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
	this->str = nullptr;
}

RelationalScanCondition::~RelationalScanCondition() {
	delete this->left;
	delete this->right;
	resetStr();
}

void RelationalScanCondition::setLeft(IValueProvider* element) {
	this->left = element;
	resetStr();
}

void RelationalScanCondition::setRight(IValueProvider* element) {
	this->right = element;
	resetStr();
}

void RelationalScanCondition::setOp(uint8_t op) noexcept {
	this->op = op;
}

const UnicodeString* RelationalScanCondition::toStringCode() noexcept {
	if(this->str == nullptr){
		resetStr();
		this->str = new UnicodeString(L"");

		AbstractScanCondition* cond = dynamic_cast<AbstractScanCondition*>(this->left);
		this->str->append(cond->toStringCode());

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

		cond = dynamic_cast<AbstractScanCondition*>(this->right);
		this->str->append(cond->toStringCode());
	}

	return this->str;
}

void RelationalScanCondition::resetStr() noexcept {
	if(this->str != nullptr){
		delete this->str;
		this->str = nullptr;
	}
}

} /* namespace codablecash */
