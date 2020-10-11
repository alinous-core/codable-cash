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
class DropTableLog;
class InsertLog;
class CdbTable;
class AbstractAlterCommandLog;
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
	void rollback(bool force);

	void createTable(CreateTableLog* cmd);
	void dropTable(DropTableLog* cmd);
	void alterTable(AbstractAlterCommandLog* cmd);

	void insert(InsertLog* cmd);

	void reset() noexcept;

	uint64_t getSchemaObjectVersionId() const noexcept;
	CdbTable* getTable(const UnicodeString* schema, const UnicodeString* tableName) const noexcept;

	const UnicodeString* getCurrentSchema() const noexcept {
		return currentSchema;
	}

	CdbTransaction* getTransaction() const noexcept {
		return this->trx;
	}

private:
	void doCommit();
	void doRollback();

private:
	CodableDatabase* db;
	CdbTransaction* trx;

	UnicodeString* currentSchema;
};

} /* namespace alinous */

#endif /* VM_TRX_VMTRANSACTIONHANDLER_H_ */
