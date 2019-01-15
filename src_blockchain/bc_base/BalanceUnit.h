/*
 * BalanceUnit.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_BALANCEUNIT_H_
#define BC_BASE_BALANCEUNIT_H_

#include <inttypes.h>

#include "filestore_block/IBlockObject.h"

namespace codablecash {
using namespace alinous;

class BalanceUnit : public IBlockObject {
public:
	explicit BalanceUnit(uint64_t amount);
	virtual ~BalanceUnit();

	uint64_t getAmount() const noexcept;
	void setAmount(uint64_t amount) noexcept{this->amount = amount;}

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	void importBinary(ByteBuffer* in);
private:
	uint64_t amount;
};

} /* namespace codablecash */

#endif /* BC_BASE_BALANCEUNIT_H_ */
