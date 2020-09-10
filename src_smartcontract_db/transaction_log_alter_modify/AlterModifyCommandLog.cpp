/*
 * AlterModifyCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterModifyCommandLog.h"

namespace codablecash {

AlterModifyCommandLog::AlterModifyCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_MODIFY) {

}

AlterModifyCommandLog::~AlterModifyCommandLog() {

}

int AlterModifyCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterModifyCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterModifyCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterModifyCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
