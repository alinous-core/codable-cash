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

}

void EqualityScanCondition::setLeft(AbstractScanConditionElement* element) {
	this->left = dynamic_cast<IValueProvider*>(element);
	if(this->left == nullptr){
		delete element;
		throw new CdbException(L"", __FILE__, __LINE__);
	}
}

void EqualityScanCondition::setRight(AbstractScanConditionElement* element) {
	this->right = dynamic_cast<IValueProvider*>(element);
	if(this->right == nullptr){
		delete element;
		throw new CdbException(L"", __FILE__, __LINE__);
	}
}

} /* namespace codablecash */
