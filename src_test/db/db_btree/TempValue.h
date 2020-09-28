/*
 * TempValue.h
 *
 *  Created on: 2018/12/25
 *      Author: iizuka
 */

#ifndef DB_BTREE_TEMPVALUE_H_
#define DB_BTREE_TEMPVALUE_H_

#include <cstdint>

#include "filestore_block/IBlockObject.h"
#include "btree/AbstractBtreeDataFactory.h"

namespace alinous {

class TempValue : public IBlockObject {
public:
	explicit TempValue(uint64_t value);
	virtual ~TempValue();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;

	uint64_t getValue() const {
		return value;
	}

	virtual IBlockObject* copyData() const noexcept;
private:
	uint64_t value;
};

class TmpValueFactory : public AbstractBtreeDataFactory {
public:
	static const constexpr uint32_t TMPVALUE{100};

	virtual ~TmpValueFactory();

	virtual IBlockObject* makeDataFromBinary(ByteBuffer* in);
	virtual AbstractBtreeDataFactory* copy() const noexcept{ return new TmpValueFactory(); }
};

} /* namespace alinous */

#endif /* DB_BTREE_TEMPVALUE_H_ */
