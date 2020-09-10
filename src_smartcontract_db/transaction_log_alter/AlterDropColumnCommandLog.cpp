/*
 * AlterDropColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterDropColumnCommandLog.h"

namespace codablecash {

AlterDropColumnCommandLog::AlterDropColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_DROP_COLUMN) {

}

AlterDropColumnCommandLog::~AlterDropColumnCommandLog() {

}

int AlterDropColumnCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterDropColumnCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterDropColumnCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterDropColumnCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
