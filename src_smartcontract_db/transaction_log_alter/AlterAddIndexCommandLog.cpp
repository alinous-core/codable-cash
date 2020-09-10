/*
 * AlterAddIndexCommandLog.cpp
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#include "transaction_log_alter/AlterAddIndexCommandLog.h"

namespace codablecash {

AlterAddIndexCommandLog::AlterAddIndexCommandLog() : AbstractDdlLog(AbstractTransactionLog::TRX_ALTER_ADD_INDEX) {

}

AlterAddIndexCommandLog::~AlterAddIndexCommandLog() {

}

int AlterAddIndexCommandLog::binarySize() const {
	int total = sizeof(uint16_t);

	return total;
}

void AlterAddIndexCommandLog::toBinary(ByteBuffer* out) const {
}

void AlterAddIndexCommandLog::fromBinary(ByteBuffer* in) {
}

void AlterAddIndexCommandLog::commit(CdbTransactionManager* trxManager) {
}

} /* namespace codablecash */
