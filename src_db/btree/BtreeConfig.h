/*
 * BtreeConfig.h
 *
 *  Created on: 2018/12/22
 *      Author: iizuka
 */

#ifndef BTREE_BTREECONFIG_H_
#define BTREE_BTREECONFIG_H_

#include <inttypes.h>

#include "filestore_block/IBlockObject.h"

namespace alinous {

class BtreeConfig : public IBlockObject {
public:
	explicit BtreeConfig(const BtreeConfig* inst);
	BtreeConfig();
	virtual ~BtreeConfig();

	virtual int binarySize();
	virtual void toBinary(ByteBuffer* out);

	uint64_t blockSize;
	uint64_t nodeNumber;
};

} /* namespace alinous */

#endif /* BTREE_BTREECONFIG_H_ */
