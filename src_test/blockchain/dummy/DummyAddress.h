/*
 * DummyAddress.h
 *
 *  Created on: 2019/01/04
 *      Author: iizuka
 */

#ifndef BLOCKCHAIN_DUMMYADDRESS_H_
#define BLOCKCHAIN_DUMMYADDRESS_H_

#include "bc_base/AbstractAddress.h"

namespace codablecash {

class AbstractAddress;

class DummyAddress: public AbstractAddress {
public:
	DummyAddress();
	virtual ~DummyAddress();
	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual AbstractAddress* clone() const noexcept;
	virtual bool equals(const AbstractAddress* other) const noexcept;
};

} /* namespace codablecash */

#endif /* BLOCKCHAIN_DUMMYADDRESS_H_ */
