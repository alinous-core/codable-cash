/*
 * BtreeHeaderBlock.h
 *
 *  Created on: 2018/12/22
 *      Author: iizuka
 */

#ifndef BTREE_BTREEHEADERBLOCK_H_
#define BTREE_BTREEHEADERBLOCK_H_

#include <inttypes.h>

#include "filestore_block/IBlockObject.h"

namespace alinous {

class BtreeConfig;

class BtreeHeaderBlock : public IBlockObject {
public:
	BtreeHeaderBlock();
	virtual ~BtreeHeaderBlock();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;

	static BtreeHeaderBlock* fromBinary(ByteBuffer* in);

	BtreeConfig* getConfig() const noexcept {
		return config;
	}
	void setConfig(BtreeConfig* config) noexcept;

	uint64_t getRootFpos() const {
		return rootFpos;
	}
	void setRootFpos(uint64_t rootFpos) {
		this->rootFpos = rootFpos;
	}

private:
	uint64_t rootFpos;
	BtreeConfig* config;
};

} /* namespace alinous */

#endif /* BTREE_BTREEHEADERBLOCK_H_ */
