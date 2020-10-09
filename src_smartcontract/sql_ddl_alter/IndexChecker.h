/*
 * IndexChecker.h
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_INDEXCHECKER_H_
#define SQL_DDL_ALTER_INDEXCHECKER_H_

#include "base/ArrayList.h"
#include <cstdint>

using alinous::ArrayList;

namespace codablecash {

class CodableDatabase;
class CdbTable;
class CdbTableColumn;
class CdbRecordKey;
class CdbRecord;
class ColumnModifyContext;
class AbstractCdbValue;
class CdbOid;

class IndexChecker {
public:
	IndexChecker(CodableDatabase* db, const ColumnModifyContext* modifyContext);
	explicit IndexChecker(CodableDatabase* db);
	virtual ~IndexChecker();

	bool checkUnique(const CdbTable* table, const ArrayList<const CdbOid>* columnOidlist, bool update);
	bool checkUnique(const CdbTable* table, const CdbTableColumn* column, bool update);
	bool checkUnique(const CdbTable* table, ArrayList<const CdbTableColumn>* columnList, bool update);

private:
	CdbRecordKey* makeIndexKey(const CdbRecord* record, ArrayList<const CdbTableColumn>* columnList);
	CdbRecord* getConvertedRecord(const CdbRecord* record);

private:
	CodableDatabase* const db;

	// values used by record converter
	int pos;
	bool isnotnull;
	uint8_t cdbType;
	int length;
	const AbstractCdbValue* defaultValue;
};

} /* namespace codablecash */

#endif /* SQL_DDL_ALTER_INDEXCHECKER_H_ */
