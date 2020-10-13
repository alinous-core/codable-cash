/*
 * TransactionLogFactory.cpp
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#include "trx/transaction_log/TransactionLogFactory.h"
#include "trx/transaction_log/AbstractTransactionLog.h"
#include "trx/transaction_log/CreateTableLog.h"
#include "trx/transaction_log/DropTableLog.h"
#include "trx/transaction_log/InsertLog.h"

#include "base_io/ByteBuffer.h"

#include "engine/CdbException.h"

#include "trx/transaction_log_alter/AlterAddColumnCommandLog.h"
#include "trx/transaction_log_alter/AlterAddIndexCommandLog.h"
#include "trx/transaction_log_alter/AlterDropIndexCommandLog.h"
#include "trx/transaction_log_alter/AlterDropColumnCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterAddPrimaryKeyCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterDropPrimaryKeyCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterModifyCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterRenameColumnCommandLog.h"
#include "trx/transaction_log_alter_modify/AlterRenameTableCommandLog.h"

namespace codablecash {

AbstractTransactionLog* TransactionLogFactory::createFromBinary(ByteBuffer* in) {
	uint8_t type = in->get();
	AbstractTransactionLog* ret = nullptr;

	switch(type){
	case AbstractTransactionLog::TRX_CREATE_TABLE:
		ret = new CreateTableLog();
		break;
	case AbstractTransactionLog::TRX_DROP_TABLE:
		ret = new DropTableLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_ADD_INDEX:
		ret = new AlterAddIndexCommandLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_ADD_COLUMN:
		ret = new AlterAddColumnCommandLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_DROP_INDEX:
		ret = new AlterDropIndexCommandLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_DROP_COLUMN:
		ret = new AlterDropColumnCommandLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_ADD_PRIMARY_KEY:
		ret = new AlterAddPrimaryKeyCommandLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_DROP_PRIMARY_KEY:
		ret = new AlterDropPrimaryKeyCommandLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_MODIFY:
		ret = new AlterModifyCommandLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_RENAME_COLUMN:
		ret = new AlterRenameColumnCommandLog();
		break;
	case AbstractTransactionLog::TRX_ALTER_RENAME_TABLE:
		ret = new AlterRenameTableCommandLog();
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
