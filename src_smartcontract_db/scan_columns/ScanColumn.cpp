/*
 * ScanColumn.cpp
 *
 *  Created on: 2020/08/19
 *      Author: iizuka
 */

#include "scan_columns/ScanColumn.h"

namespace codablecash {

ScanColumn::ScanColumn(const SQLColumnIdentifier* sqlColumnId) {
	this->sqlColumnId = sqlColumnId;
}

ScanColumn::~ScanColumn() {
	this->sqlColumnId = nullptr;
}

} /* namespace codablecash */
