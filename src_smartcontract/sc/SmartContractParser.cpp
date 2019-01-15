/*
 * SmartContractParser.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc/SmartContractParser.h"
#include "base_io/File.h"

namespace codablecash {

SmartContractParser::SmartContractParser(const File* file) {
	this->file = new File(*file);
}

SmartContractParser::~SmartContractParser() {
	delete file;
}

} /* namespace codablecash */
