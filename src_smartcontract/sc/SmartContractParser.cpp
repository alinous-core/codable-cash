/*
 * SmartContractParser.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc/SmartContractParser.h"
#include "base_io/File.h"
#include "base_io_stream/FileInputStream.h"
#include "sc/ParserReaderStream.h"

namespace codablecash {

SmartContractParser::SmartContractParser(const File* file) {
	this->file = new File(*file);
}

SmartContractParser::~SmartContractParser() {
	delete file;
}

void SmartContractParser::parse() {
	int length = this->file->length();
	FileInputStream inStream(this->file);

	ParserReaderStream readStream(&inStream, length);

}

} /* namespace codablecash */


