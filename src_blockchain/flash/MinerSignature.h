/*
 * MinerSignature.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_MINERSIGNATURE_H_
#define FLASH_MINERSIGNATURE_H_

#include "filestore_block/IBlockObject.h"

namespace codablecash {
using namespace alinous;

class NodeIdentifier;

class MinerSignature : public alinous::IBlockObject {
private:
	MinerSignature();
public:
	MinerSignature(const MinerSignature& inst);
	explicit MinerSignature(const NodeIdentifier* nodeId);
	virtual ~MinerSignature();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	static MinerSignature* fromBinary(ByteBuffer* in);

private:
	NodeIdentifier* nodeId;
};

} /* namespace codablecash */

#endif /* FLASH_MINERSIGNATURE_H_ */
