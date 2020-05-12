/*
 * CreateTableLog.cpp
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#include "transaction_log/CreateTableLog.h"

namespace codablecash {

CreateTableLog::CreateTableLog() : AbstractDdlLog(AbstractTransactionLog::TRX_CREATE_TABLE) {

}

CreateTableLog::~CreateTableLog() {

}

int CreateTableLog::binarySize() const noexcept {
}

void CreateTableLog::toBinary(ByteBuffer* out) const {
}

void CreateTableLog::fromBinary(ByteBuffer* in) {
}

} /* namespace codablecash */
