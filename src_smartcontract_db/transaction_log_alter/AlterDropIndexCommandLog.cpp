/*
 * AlterDropIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterDropIndexCommandLog.h"

namespace codablecash {

AlterDropIndexCommandLog::AlterDropIndexCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_DROP_INDEX) {

}

AlterDropIndexCommandLog::~AlterDropIndexCommandLog() {

}

int AlterDropIndexCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterDropIndexCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterDropIndexCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterDropIndexCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
