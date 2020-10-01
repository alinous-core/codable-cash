/*
 * IndexChecker.h
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_INDEXCHECKER_H_
#define SQL_DDL_ALTER_INDEXCHECKER_H_

#include "base/ArrayList.h"

using alinous::ArrayList;

namespace codablecash {

class CodableDatabase;
class CdbTable;
class CdbTableColumn;
class CdbRecordKey;
class CdbRecord;

class IndexChecker {
public:
	explicit IndexChecker(CodableDatabase* db);
	virtual ~IndexChecker();

	bool checkUnique(const CdbTable* table, const CdbTableColumn* column);
	bool checkUnique(const CdbTable* table, ArrayList<const CdbTableColumn>* column);

private:
	CdbRecordKey* makeIndexKey(const CdbRecord* record, ArrayList<const CdbTableColumn>* column);

private:
	CodableDatabase* const db;
};

} /* namespace codablecash */

#endif /* SQL_DDL_ALTER_INDEXCHECKER_H_ */
