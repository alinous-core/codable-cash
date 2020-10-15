/*
 * ScanTargetNameResolver.cpp
 *
 *  Created on: 2020/08/27
 *      Author: iizuka
 */

#include "scan_select/scan_planner/analyze/ScanTargetNameResolver.h"

#include "base/UnicodeString.h"

#include "scan_select/scan_table/AbstractScanTableTarget.h"

#include "engine/CdbException.h"

namespace codablecash {

ScanTargetNameResolver::ScanTargetNameResolver() {

}

ScanTargetNameResolver::~ScanTargetNameResolver() {

}

void ScanTargetNameResolver::add(const UnicodeString* tableFqn,	AbstractScanTableTarget* target) {
	AbstractScanTableTarget* last = get(tableFqn);
	if(last != nullptr){
		throw new CdbException(L"table name already defined", __FILE__, __LINE__);
	}

	this->map.put(tableFqn, target);
}

AbstractScanTableTarget* ScanTargetNameResolver::get(const UnicodeString* tableFqn) const noexcept {
	return this->map.get(tableFqn);
}

} /* namespace codablecash */
