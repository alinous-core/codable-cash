/*
 * RightTableIndexTransactionScanner.h
 *
 *  Created on: 2020/12/20
 *      Author: iizuka
 */

#ifndef TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_
#define TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_

#include "trx/scan/transaction_scanner_join/IJoinRightSource.h"

#include "trx/scan/transaction_scanner/AbstractTransactionScanner.h"

namespace codablecash {

class CdbTableIndex;
class IndexStore;
class IndexScanner;

class RightTableIndexTransactionScanner : public IJoinRightSource, public AbstractTransactionScanner {
public:
	RightTableIndexTransactionScanner(ScanResultMetadata* metadata, CdbTransaction* trx,
			const CdbTable* table, const AbstractScanCondition* filterCondition, CdbTableIndex* index);
	virtual ~RightTableIndexTransactionScanner();

	virtual void start();
	virtual void reset(const AbstractCdbKey* key);

	virtual bool hasNext();
	virtual const CdbRecord* next();

	virtual void shutdown();

private:
	void setScanner(IndexScanner* scanner) noexcept;

private:
	CdbTableIndex* index;
	IndexStore* indexStore;
	IndexScanner* scanner;
};

} /* namespace codablecash */

#endif /* TRX_SCAN_TRANSACTION_SCANNER_JOIN_RIGHT_RIGHTTABLEINDEXTRANSACTIONSCANNER_H_ */
