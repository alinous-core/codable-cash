/*
 * BtreeConfig.h
 *
 *  Created on: 2018/12/22
 *      Author: iizuka
 */

#ifndef BTREE_BTREECONFIG_H_
#define BTREE_BTREECONFIG_H_

#include <cstdint>

#include "filestore_block/IBlockObject.h"

namespace alinous {

class BtreeConfig : public IBlockObject {
public:
	explicit BtreeConfig(const BtreeConfig* inst);
	BtreeConfig();
	virtual ~BtreeConfig();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static BtreeConfig* fromBinary(ByteBuffer* in);

	virtual IBlockObject* copyData() const noexcept;

	uint64_t blockSize;
	uint64_t nodeNumber;
};

} /* namespace alinous */

#endif /* BTREE_BTREECONFIG_H_ */
