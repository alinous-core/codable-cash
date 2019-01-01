/*
 * BlockchainsConfig.cpp
 *
 *  Created on: 2019/01/01
 *      Author: iizuka
 */

#include "bc/BlockchainsConfig.h"

#include "base_io/File.h"

namespace codablecash {

BlockchainsConfig::BlockchainsConfig(const BlockchainsConfig& inst) {
	this->numShards = inst.numShards;

	this->baseFolder = inst.baseFolder != nullptr ? new File(*inst.baseFolder) : nullptr;
}

BlockchainsConfig::~BlockchainsConfig() {
	if(this->baseFolder != nullptr){
		delete this->baseFolder;
	}
}


BlockchainsConfig::BlockchainsConfig() {
	this->numShards = 4;
	this->baseFolder = nullptr;
}


} /* namespace codablecash */


