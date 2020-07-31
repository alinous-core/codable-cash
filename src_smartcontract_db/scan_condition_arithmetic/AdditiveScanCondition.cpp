/*
 * AdditiveScanCondition.cpp
 *
 *  Created on: 2020/07/31
 *      Author: iizuka
 */

#include "scan_condition_arithmetic/AdditiveScanCondition.h"

#include "sc/CodeElement.h"

namespace codablecash {

AdditiveScanCondition::AdditiveScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_ADDITIVE){

}

AdditiveScanCondition::~AdditiveScanCondition() {
	this->list.deleteElements();
}

} /* namespace codablecash */
