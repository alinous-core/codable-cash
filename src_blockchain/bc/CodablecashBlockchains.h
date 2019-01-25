/*
 * Blockchains.h
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#ifndef BC_CODABLECASHBLOCKCHAINS_H_
#define BC_CODABLECASHBLOCKCHAINS_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

class BlockchainsConfig;
class NetworkShardsStatus;
class FlashBlockchain;
class Blockchain;


class CodablecashBlockchains {
public:
	CodablecashBlockchains(const CodablecashBlockchains& inst) = delete;
	explicit CodablecashBlockchains(const BlockchainsConfig* config);
	virtual ~CodablecashBlockchains();

	void init();

private:
	BlockchainsConfig* config;
	NetworkShardsStatus* shardStatus;
	FlashBlockchain* flashChain;
	Blockchain* blockchain;

	File* baseDir;

};

} /* namespace codablecash */

#endif /* BC_CODABLECASHBLOCKCHAINS_H_ */
