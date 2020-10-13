/*
 * AbstractScanCondition.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan_select/scan_condition/AbstractScanCondition.h"

#include "engine/CdbException.h"

namespace codablecash {

AbstractScanCondition::AbstractScanCondition(short type) {
	this->type = type;
}

AbstractScanCondition::~AbstractScanCondition() {

}

bool AbstractScanCondition::isContainer() const noexcept {
	return false;
}

} /* namespace codablecash */
