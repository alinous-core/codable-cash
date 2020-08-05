/*
 * LikeScanCondition.cpp
 *
 *  Created on: 2020/08/05
 *      Author: iizuka
 */

#include "scan_condition_exp/LikeScanCondition.h"

#include "sc/CodeElement.h"

namespace codablecash {

LikeScanCondition::LikeScanCondition() : AbstractScanCondition(CodeElement::SQL_EXP_LIKE) {

}

LikeScanCondition::~LikeScanCondition() {

}

} /* namespace codablecash */
