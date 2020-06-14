/*
 * TransactionLogFactory.cpp
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#include "transaction_log/TransactionLogFactory.h"
#include "transaction_log/AbstractTransactionLog.h"
#include "transaction_log/CreateTableLog.h"
#include "transaction_log/InsertLog.h"

#include "base_io/ByteBuffer.h"

#include "engine/CdbException.h"


namespace codablecash {

AbstractTransactionLog* TransactionLogFactory::createFromBinary(ByteBuffer* in) {
	uint8_t type = in->get();
	AbstractTransactionLog* ret = nullptr;

	switch(type){
	case AbstractTransactionLog::TRX_CREATE_TABLE:
		ret = new CreateTableLog();
		break;
	case AbstractTransactionLog::TRX_INSERT:
		ret = new InsertLog();
		break;
	default:
		throw new CdbException(L"Transaction log type is wrong.", __FILE__, __LINE__);
	}

	ret->fromBinary(in);

	return ret;
}


} /* namespace codablecash */
