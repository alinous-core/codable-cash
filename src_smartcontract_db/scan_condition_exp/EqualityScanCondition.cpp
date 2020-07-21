/*
 * EqualityScanCondition.cpp
 *
 *  Created on: 2020/07/20
 *      Author: iizuka
 */

#include "scan_condition_exp/EqualityScanCondition.h"

#include "sc/CodeElement.h"
namespace alinous {

EqualityScanCondition::EqualityScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_EQUALITY) {

}

EqualityScanCondition::~EqualityScanCondition() {

}

} /* namespace alinous */
