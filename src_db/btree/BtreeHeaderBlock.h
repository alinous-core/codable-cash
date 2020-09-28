/*
 * BtreeHeaderBlock.h
 *
 *  Created on: 2018/12/22
 *      Author: iizuka
 */

#ifndef BTREE_BTREEHEADERBLOCK_H_
#define BTREE_BTREEHEADERBLOCK_H_

#include <cstdint>

#include "filestore_block/IBlockObject.h"

namespace alinous {

class BtreeConfig;

class BtreeHeaderBlock : public IBlockObject {
public:
	BtreeHeaderBlock &operator=(const BtreeHeaderBlock &o) = delete;

	BtreeHeaderBlock(const BtreeHeaderBlock& inst);
	BtreeHeaderBlock();
	virtual ~BtreeHeaderBlock();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;

	static BtreeHeaderBlock* fromBinary(ByteBuffer* in);

	BtreeConfig* getConfig() const noexcept {
		return config;
	}
	void setConfig(const BtreeConfig* config) noexcept;

	uint64_t getRootFpos() const {
		return rootFpos;
	}
	void setRootFpos(uint64_t rootFpos) {
		this->rootFpos = rootFpos;
	}

	virtual IBlockObject* copyData() const noexcept;

private:
	uint64_t rootFpos;
	BtreeConfig* config;
};

} /* namespace alinous */

#endif /* BTREE_BTREEHEADERBLOCK_H_ */
