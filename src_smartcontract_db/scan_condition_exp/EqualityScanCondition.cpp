/*
 * EqualityScanCondition.cpp
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#include "scan_condition_exp/EqualityScanCondition.h"

#include "sc/CodeElement.h"

#include "scan_condition/IValueProvider.h"

#include "engine/CdbException.h"

using namespace alinous;

namespace codablecash {

EqualityScanCondition::EqualityScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_EQUALITY) {
	this->left = nullptr;
	this->right = nullptr;
}

EqualityScanCondition::~EqualityScanCondition() {
	delete this->left;
	delete this->right;
}

void EqualityScanCondition::setLeft(IValueProvider* element) {
	this->left = element;
	if(this->left == nullptr){
		delete element;
		throw new CdbException(L"The left element is not value provider", __FILE__, __LINE__);
	}
}

void EqualityScanCondition::setRight(IValueProvider* element) {
	this->right = element;
}

} /* namespace codablecash */
