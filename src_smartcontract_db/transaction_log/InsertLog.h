/*
 * InsertLog.h
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_INSERTLOG_H_
#define TRANSACTION_LOG_INSERTLOG_H_

#include "transaction_log/AbstractTransactionLog.h"

namespace codablecash {

class CdbRecord;

class InsertLog : public AbstractTransactionLog {
public:
	InsertLog();
	virtual ~InsertLog();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

private:
	CdbRecord* record;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_INSERTLOG_H_ */
