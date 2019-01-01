/*
 * BlockchainsConfig.h
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#ifndef BC_BLOCKCHAINSCONFIG_H_
#define BC_BLOCKCHAINSCONFIG_H_

namespace alinous {
class File;
}

namespace codablecash {
using namespace alinous;

/**
 * load config from file
 */
class BlockchainsConfig {
public:
	BlockchainsConfig(const BlockchainsConfig& inst);
	BlockchainsConfig();
	~BlockchainsConfig();

public:
	int numShards;
	File* baseFolder;

};

} /* namespace codablecash */

#endif /* BC_BLOCKCHAINSCONFIG_H_ */
