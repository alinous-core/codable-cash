/*
 * RecordScanner.cpp
 *
 *  Created on: 2020/06/11
 *      Author: iizuka
 */

#include "scan/RecordScanner.h"

namespace codablecash {

RecordScanner::RecordScanner(TableStore* tableStore) {
	this->tableStore = tableStore;
}

RecordScanner::~RecordScanner() {
	this->tableStore = nullptr;
}

void RecordScanner::start() {
}

} /* namespace codablecash */
