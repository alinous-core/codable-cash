/*
 * ScanResultExecutor.cpp
 *
 *  Created on: 2021/01/21
 *      Author: iizuka
 */

#include "trx/scan/transaction_scan_result/ScanResultExecutor.h"

#include "trx/scan/transaction_scanner_join/IJoinLeftSource.h"

namespace codablecash {

ScanResultExecutor::ScanResultExecutor(IJoinLeftSource* source) {
	this->source = source;
}

ScanResultExecutor::~ScanResultExecutor() {
	this->source = nullptr;
}

} /* namespace codablecash */
