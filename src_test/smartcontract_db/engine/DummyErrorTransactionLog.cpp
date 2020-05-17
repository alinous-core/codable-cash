/*
 * DummyErrorTransactionLog.cpp
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#include "DummyErrorTransactionLog.h"

#include "transaction_log/AbstractTransactionLog.h"

#include "engine/CdbException.h"


namespace codablecash {

DummyErrorTransactionLog::DummyErrorTransactionLog() {

}

DummyErrorTransactionLog::~DummyErrorTransactionLog() {

}

void DummyErrorTransactionLog::commit(CdbTransactionManager* trxManager) {
	throw new CdbException(__FILE__, __LINE__);
}

} /* namespace codablecash */
