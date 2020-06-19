/*
 * VmTransactionHandler.h
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#ifndef VM_TRX_VMTRANSACTIONHANDLER_H_
#define VM_TRX_VMTRANSACTIONHANDLER_H_

#include <cstdint>

namespace codablecash {
class CodableDatabase;
class CdbTransaction;
class CreateTableLog;
class InsertLog;
class CdbTable;
}
using namespace codablecash;

namespace alinous {

class UnicodeString;

class VmTransactionHandler {
public:
	explicit VmTransactionHandler(CodableDatabase* db);
	virtual ~VmTransactionHandler();

	void begin();
	void commit();
	void rollback();

	void createTable(CreateTableLog* cmd);

	void insert(InsertLog* cmd);

	void reset() noexcept;

	uint64_t getSchemaObjectVersionId() const noexcept;
	CdbTable* getTable(const UnicodeString* schema, const UnicodeString* tableName) const noexcept;

private:
	void doCommit();
	void doRollback();

private:
	CodableDatabase* db;
	CdbTransaction* trx;
};

} /* namespace alinous */

#endif /* VM_TRX_VMTRANSACTIONHANDLER_H_ */
