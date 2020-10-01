/*
 * IndexChecker.h
 *
 *  Created on: 2020/10/01
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_INDEXCHECKER_H_
#define SQL_DDL_ALTER_INDEXCHECKER_H_

namespace codablecash {

class SchemaManager;
class CdbStorageManager;

class IndexChecker {
public:
	IndexChecker(SchemaManager* scmagr, CdbStorageManager* storagemgr);
	virtual ~IndexChecker();

private:
	SchemaManager* const scmagr;
	CdbStorageManager* const storagemgr;
};

} /* namespace codablecash */

#endif /* SQL_DDL_ALTER_INDEXCHECKER_H_ */
