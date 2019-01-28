/*
 * MinerSignature.h
 *
 *  Created on: 2019/01/25
 *      Author: iizuka
 */

#ifndef FLASH_MINERSIGNATURE_H_
#define FLASH_MINERSIGNATURE_H_

namespace codablecash {

class NodeIdentifier;

class MinerSignature {
public:
	MinerSignature(const MinerSignature& inst) = default;
	MinerSignature(NodeIdentifier* nodeId);
	virtual ~MinerSignature();

private:
	NodeIdentifier* nodeId;
};

} /* namespace codablecash */

#endif /* FLASH_MINERSIGNATURE_H_ */
