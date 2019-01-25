/*
 * TransactionInput.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_TRANSACTIONINPUT_H_
#define BC_BASE_TRANSACTIONINPUT_H_

#include <cstdint>

#include "filestore_block/IBlockObject.h"

namespace codablecash {
using namespace alinous;

class BalanceUnit;
class AbstractAddress;

class TransactionInput : public IBlockObject {
private:
	TransactionInput();
public:
	TransactionInput(const TransactionInput& inst);
	TransactionInput(const AbstractAddress* address, uint64_t amount);
	virtual ~TransactionInput();

	uint64_t getBalanceAmount() const noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static TransactionInput* fromBinary(ByteBuffer* in);
private:
	BalanceUnit* balance;
	AbstractAddress* address;

};

} /* namespace codablecash */

#endif /* BC_BASE_TRANSACTIONINPUT_H_ */
