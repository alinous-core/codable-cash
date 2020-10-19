/*
 * AllScanColumns.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_select/scan_columns/AllScanColumns.h"

#include "base/UnicodeString.h"

namespace codablecash {

AllScanColumns::AllScanColumns() {

}

AllScanColumns::~AllScanColumns() {

}

const UnicodeString* AllScanColumns::toStringCode() noexcept {
	if(this->str == nullptr){
		this->str = new UnicodeString(L"*");
	}

	return this->str;
}

void AllScanColumns::resolveColumns(VirtualMachine* vm, SelectScanPlanner* planner) {

}


} /* namespace codablecash */
