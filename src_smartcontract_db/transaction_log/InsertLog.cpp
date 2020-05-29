/*
 * InsertLog.cpp
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#include "transaction_log/InsertLog.h"

#include "base_io/ByteBuffer.h"

#include "table_record/CdbRecord.h"


namespace codablecash {

InsertLog::InsertLog() : AbstractTransactionLog(AbstractTransactionLog::TRX_INSERT) {
	this->record = nullptr;
}

InsertLog::~InsertLog() {
	delete this->record;
}

int InsertLog::binarySize() const {
	int total = sizeof(uint8_t);

	return total;
}

void InsertLog::toBinary(ByteBuffer* out) const {
	out->put(AbstractTransactionLog::TRX_INSERT);
}

void InsertLog::fromBinary(ByteBuffer* in) {
}

void InsertLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
