/*
 * AlterRenameTableCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter_modify/AlterRenameTableCommandLog.h"

namespace codablecash {

AlterRenameTableCommandLog::AlterRenameTableCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_RENAME_TABLE) {

}

AlterRenameTableCommandLog::~AlterRenameTableCommandLog() {

}

int AlterRenameTableCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterRenameTableCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterRenameTableCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterRenameTableCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
