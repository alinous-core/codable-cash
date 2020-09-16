/*
 * CdbTransaction.h
 *
 *  Created on: 2020/05/11
 *      Author: iizuka
 */

#ifndef TRANSACTION_CDBTRANSACTION_H_
#define TRANSACTION_CDBTRANSACTION_H_
#include <cstdint>

#include "base/ArrayList.h"

using namespace alinous;

namespace codablecash {

class CdbTransactionManager;
class AbstractTransactionLog;
class CreateTableLog;
class InsertLog;
class TableTransactionScanner;
class AbstractScanCondition;
class CdbTableIdentifier;
class TransactionUpdateCache;
class CdbTable;
class IndexScanner;
class CdbOid;
class AbstractCdbKey;
class CdbRecordKey;
class IndexRecordScanner;
class TableStore;
class IndexStore;
class AbstractDdlLog;

class CdbTransaction {
public:
	CdbTransaction(CdbTransactionManager* trxManager, uint64_t transactionId);
	virtual ~CdbTransaction();

	void commit();
	void rollback();

	void createTable(CreateTableLog* cmd);
	void alterTable(AbstractDdlLog* cmd);

	void insert(InsertLog* cmd);

	TableTransactionScanner* getTableTransactionScanner(const CdbTableIdentifier* tableId, AbstractScanCondition* condition);

	IndexScanner* getRawIndexScanner(const CdbTableIdentifier* tableId, const UnicodeString* columnName,
			CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq);
	IndexScanner* getRawIndexScanner(const CdbTableIdentifier* tableId, const ArrayList<const UnicodeString>* columnlist,
			CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq);
	IndexScanner* getRawIndexScanner(const CdbTableIdentifier* tableId, const ArrayList<const CdbOid>* columnOidList,
			CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq);

	IndexRecordScanner* getIndexRecordScanner(const CdbTableIdentifier* tableId, const UnicodeString* columnName,
			CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq);
	IndexRecordScanner* getIndexRecordScanner(const CdbTableIdentifier* tableId, const ArrayList<const UnicodeString>* columnlist,
			CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq);
	IndexRecordScanner* getIndexRecordScanner(const CdbTableIdentifier* tableId, const ArrayList<const CdbOid>* columnOidList,
			CdbRecordKey* begin, bool beginEq, CdbRecordKey* end, bool endEq);

	TransactionUpdateCache* getUpdateCache() const noexcept;

	CdbTransactionManager* getTrxManager() const noexcept {
		return trxManager;
	}

private:
	CdbTable* getTableFromIdentifier(const CdbTableIdentifier* tableId) const;
	TableStore* getTableStoreFromIdentifier(const CdbTableIdentifier* tableId) const;
	IndexStore* getIndexStoreFromIdentifier(const CdbTableIdentifier* tableId, const ArrayList<const CdbOid>* columnOidList) const;

	void convertColumnName2OidList(const CdbTable* table, const ArrayList<const UnicodeString>* columnlist, ArrayList<const CdbOid>* columnOidList) const;
private:
	CdbTransactionManager* trxManager;
	uint64_t transactionId;

	ArrayList<AbstractTransactionLog> cmdList;
	TransactionUpdateCache* updateCache;
};

} /* namespace codablecash */

#endif /* TRANSACTION_CDBTRANSACTION_H_ */
