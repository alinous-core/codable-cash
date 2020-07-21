/*
 * AbstractScanCondition.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan_condition/AbstractScanCondition.h"

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

void AbstractScanCondition::addCondition(AbstractScanCondition* cond) {
	throw new CdbException(L"addCondition() is not supported.", __FILE__, __LINE__);
}

} /* namespace codablecash */
