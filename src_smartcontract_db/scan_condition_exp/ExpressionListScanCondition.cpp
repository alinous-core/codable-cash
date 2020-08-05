/*
 * ExpressionListScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_exp/ExpressionListScanCondition.h"

#include "sc/CodeElement.h"

namespace codablecash {

ExpressionListScanCondition::ExpressionListScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_EXP_LIST) {

}

ExpressionListScanCondition::~ExpressionListScanCondition() {

}

} /* namespace codablecash */
