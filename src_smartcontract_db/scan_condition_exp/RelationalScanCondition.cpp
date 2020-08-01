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

using namespace alinous;

namespace codablecash {

RelationalScanCondition::RelationalScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_RELATIONAL) {
	this->left = nullptr;
	this->right = nullptr;
	this->op = 0;
}

RelationalScanCondition::~RelationalScanCondition() {
	delete this->left;
	delete this->right;
}

void RelationalScanCondition::setLeft(IValueProvider* element) {
	this->left = element;
	if(this->left == nullptr){
		delete element;
		throw new CdbException(L"The left element is not value provider", __FILE__, __LINE__);
	}
}

void RelationalScanCondition::setRight(IValueProvider* element) {
	this->right = element;
}

void RelationalScanCondition::setOp(uint8_t op) noexcept {
	this->op = op;
}

} /* namespace codablecash */
