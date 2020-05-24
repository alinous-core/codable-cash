/*
 * VmTransactionHandler.h
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#ifndef VM_TRX_VMTRANSACTIONHANDLER_H_
#define VM_TRX_VMTRANSACTIONHANDLER_H_

namespace codablecash {
class CodableDatabase;
class CdbTransaction;
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

private:
	void doRollback();

private:
	CodableDatabase* db;
	CdbTransaction* trx;
};

} /* namespace alinous */

#endif /* VM_TRX_VMTRANSACTIONHANDLER_H_ */
