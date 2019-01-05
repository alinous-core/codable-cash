/*
 * TransactionId.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONID_H_
#define BC_BASE_TRANSACTIONID_H_

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class TransactionId {
public:
	TransactionId(const char* binary, int length);
	virtual ~TransactionId();

private:
	ByteBuffer* id; // 32 bytes
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONID_H_ */
