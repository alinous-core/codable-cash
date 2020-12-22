/*
 * AbstractTransactionScanner.h
 *
 *  Created on: 2020/06/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCANNER_ABSTRACTTRANSACTIONSCANNER_H_
#define TRANSACTION_SCANNER_ABSTRACTTRANSACTIONSCANNER_H_

namespace codablecash {

class CdbTransaction;
class CdbRecord;
class CdbTable;
class InsertRecordsCacheCursor;
class ScanResultMetadata;

class AbstractTransactionScanner {
public:
	AbstractTransactionScanner(const ScanResultMetadata* metadata, CdbTransaction* trx, const CdbTable* table);
	virtual ~AbstractTransactionScanner();

	virtual void start() = 0;
	virtual bool hasNext() = 0;
	virtual const CdbRecord* next() = 0;

	virtual void shutdown() = 0;

	bool hasInsertedRecord() const noexcept;
	const CdbRecord* nextInsertedRecord() noexcept;

	const CdbRecord* checkUpdated(const CdbRecord* record) const noexcept;
protected:
	ScanResultMetadata* metadata;
	CdbTransaction* trx;
	const CdbTable* table;
	InsertRecordsCacheCursor* cacheCursor;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCANNER_ABSTRACTTRANSACTIONSCANNER_H_ */
