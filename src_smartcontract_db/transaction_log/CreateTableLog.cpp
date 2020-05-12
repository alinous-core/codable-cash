/*
 * CreateTableLog.cpp
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#include "transaction_log/CreateTableLog.h"

#include "base_io/ByteBuffer.h"


namespace codablecash {

CreateTableLog::CreateTableLog() : AbstractDdlLog(AbstractTransactionLog::TRX_CREATE_TABLE) {

}

CreateTableLog::~CreateTableLog() {

}

int CreateTableLog::binarySize() const noexcept {
	int total = sizeof(uint8_t);

	return total;
}

void CreateTableLog::toBinary(ByteBuffer* out) const {
	out->put(AbstractTransactionLog::TRX_CREATE_TABLE);
}

void CreateTableLog::fromBinary(ByteBuffer* in) {

}

} /* namespace codablecash */
