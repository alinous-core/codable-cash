/*
 * AbstractScanCondition.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan_condition/AbstractScanCondition.h"

namespace codablecash {

AbstractScanCondition::AbstractScanCondition(short type) {
	this->type = type;
}

AbstractScanCondition::~AbstractScanCondition() {

}

} /* namespace codablecash */
