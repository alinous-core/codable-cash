/*
 * InsertLog.h
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_INSERTLOG_H_
#define TRANSACTION_LOG_INSERTLOG_H_

#include "trx/transaction_log/AbstractTransactionLog.h"

#include "base/ArrayList.h"

namespace codablecash {

class CdbRecord;
class CdbTableIdentifier;

class InsertLog : public AbstractTransactionLog {
public:
	InsertLog();
	virtual ~InsertLog();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

	void addRecord(CdbRecord* record) noexcept;
	void setTable(CdbTableIdentifier* table) noexcept;
	CdbTableIdentifier* getCdbTableIdentifier() const noexcept {
		return this->table;
	}

	const ArrayList<CdbRecord>* getRecords() const noexcept;
private:
	CdbTableIdentifier* table;
	ArrayList<CdbRecord> records;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_INSERTLOG_H_ */
