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
}
using namespace codablecash;

namespace alinous {

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
private:
	void doCommit();
	void doRollback();

private:
	CodableDatabase* db;
	CdbTransaction* trx;
};

} /* namespace alinous */

#endif /* VM_TRX_VMTRANSACTIONHANDLER_H_ */
