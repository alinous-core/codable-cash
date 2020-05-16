/*
 * DummyErrorTransactionLog.h
 *
 *  Created on: 2020/05/16
 *      Author: iizuka
 */

#ifndef SMARTCONTRACT_DB_ENGINE_DUMMYERRORTRANSACTIONLOG_H_
#define SMARTCONTRACT_DB_ENGINE_DUMMYERRORTRANSACTIONLOG_H_

#include "transaction_log/CreateTableLog.h"

namespace codablecash {

class DummyErrorTransactionLog : public CreateTableLog {
public:
	DummyErrorTransactionLog();
	virtual ~DummyErrorTransactionLog();

	virtual void commit(CdbTransactionManager* trxManager);
};

} /* namespace codablecash */

#endif /* SMARTCONTRACT_DB_ENGINE_DUMMYERRORTRANSACTIONLOG_H_ */
