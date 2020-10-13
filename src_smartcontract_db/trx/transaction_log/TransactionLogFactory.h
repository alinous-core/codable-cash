/*
 * TransactionLogFactory.h
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_TRANSACTIONLOGFACTORY_H_
#define TRANSACTION_LOG_TRANSACTIONLOGFACTORY_H_

namespace alinous {
class ByteBuffer;
}
using namespace alinous;

namespace codablecash {

class AbstractTransactionLog;

class TransactionLogFactory {
public:
	static AbstractTransactionLog* createFromBinary(ByteBuffer* in);
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_TRANSACTIONLOGFACTORY_H_ */
