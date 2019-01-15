/*
 * SmartContractParser.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "sc/SmartContractParser.h"
#include "sc/ParserReaderStream.h"

#include "base_io/File.h"
#include "base_io_stream/FileInputStream.h"

#include "alinous_lang/CharStream.h"
#include "alinous_lang/AlinousLangTokenManager.h"
#include "alinous_lang/AlinousLang.h"

namespace codablecash {
using namespace alinouslang;

SmartContractParser::SmartContractParser(const File* file) {
	this->file = new File(*file);
}

SmartContractParser::~SmartContractParser() {
	delete file;
}

CompilationUnit* SmartContractParser::parse() {
	int length = this->file->length();
	FileInputStream inStream(this->file);

	inStream.open();

	ParserReaderStream readStream(&inStream, length);
	CharStream charStream(&readStream);

	AlinousLangTokenManager tokenManager(&charStream);

	AlinousLang alinousLang(&tokenManager);

	return alinousLang.compilationUnit();
}

} /* namespace codablecash */


