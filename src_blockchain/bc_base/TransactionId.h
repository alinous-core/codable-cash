/*
 * TransactionId.h
 *
 *  Created on: 2019/01/05
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONID_H_
#define BC_BASE_TRANSACTIONID_H_

#include "filestore_block/IBlockObject.h"

namespace alinous {
class ByteBuffer;
}

namespace codablecash {
using namespace alinous;

class TransactionId : public IBlockObject {
private:
	TransactionId();
public:
	explicit TransactionId(const TransactionId& inst);
	TransactionId(const char* binary, int length);
	virtual ~TransactionId();

	int size() const noexcept;
	const char* toArray() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static TransactionId* fromBinary(ByteBuffer* in);

private:
	ByteBuffer* id; // 32 bytes
};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONID_H_ */
