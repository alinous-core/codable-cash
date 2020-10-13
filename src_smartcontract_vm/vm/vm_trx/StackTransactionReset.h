/*
 * StackTransactionReset.h
 *
 *  Created on: 2020/05/24
 *      Author: iizuka
 */

#ifndef VM_TRX_STACKTRANSACTIONRESET_H_
#define VM_TRX_STACKTRANSACTIONRESET_H_

namespace alinous {

class VmTransactionHandler;

class StackTransactionReset {
public:
	StackTransactionReset(VmTransactionHandler* handler);
	virtual ~StackTransactionReset();

private:
	VmTransactionHandler* handler;
};

} /* namespace alinous */

#endif /* VM_TRX_STACKTRANSACTIONRESET_H_ */
