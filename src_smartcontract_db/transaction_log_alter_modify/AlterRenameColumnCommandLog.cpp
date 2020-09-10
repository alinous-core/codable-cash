/*
 * AlterRenameColumnCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterRenameColumnCommandLog.h"

namespace codablecash {

AlterRenameColumnCommandLog::AlterRenameColumnCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_RENAME_COLUMN) {

}

AlterRenameColumnCommandLog::~AlterRenameColumnCommandLog() {

}

int AlterRenameColumnCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterRenameColumnCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterRenameColumnCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterRenameColumnCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
