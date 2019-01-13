/*
 * AbstractTransaction.h
 *
 *  Created on: 2019/01/03
 *      Author: iizuka
 */

#ifndef BC_BASE_ABSTRACTTRANSACTION_H_
#define BC_BASE_ABSTRACTTRANSACTION_H_

#include "filestore_block/IBlockObject.h"

namespace codablecash {
using namespace alinous;

class AbstractTransaction : public IBlockObject {
public:
	static const constexpr int TYPE_SEND_BALANCE = 1;

	AbstractTransaction(const AbstractTransaction& inst);
	explicit AbstractTransaction(int type);
	virtual ~AbstractTransaction();

	virtual int binarySize() const = 0;
	virtual void toBinary(ByteBuffer* out) const = 0;

protected:
	int type;
};

} /* namespace codablecash */

#endif /* BC_BASE_ABSTRACTTRANSACTION_H_ */
