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

	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);

	BtreeConfig* getConfig() const {
		return config;
	}
	void setConfig(BtreeConfig* config) {
		this->config = config;
	}

private:
	uint64_t rootFpos;
	BtreeConfig* config;
};

} /* namespace alinous */

#endif /* BTREE_BTREEHEADERBLOCK_H_ */
