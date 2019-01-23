/*
 * Blockchains.h
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#ifndef BC_BLOCKCHAINS_H_
#define BC_BLOCKCHAINS_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class BlockchainsConfig;
class NetworkShardsStatus;
class FlashBlockchain;
class Blockchain;


class Blockchains {
public:
	Blockchains(const Blockchains& inst) = delete;
	explicit Blockchains(const BlockchainsConfig* config);
	virtual ~Blockchains();

	void init();

private:
	BlockchainsConfig* config;
	NetworkShardsStatus* shardStatus;
	FlashBlockchain* flashChain;
	Blockchain* blockchain;

	File* baseDir;

};

} /* namespace codablecash */

#endif /* BC_BLOCKCHAINS_H_ */
