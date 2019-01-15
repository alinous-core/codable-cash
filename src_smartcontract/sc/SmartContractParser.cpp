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
	this->inStream = nullptr;
	this->readStream = nullptr;
	this->charStream = nullptr;
	this->tokenManager = nullptr;
	this->alinousLang = nullptr;
}

SmartContractParser::~SmartContractParser() {
	delete file;

	if(this->alinousLang){
		delete this->alinousLang;
	}
	if(this->tokenManager){
		delete this->tokenManager;
	}
	if(this->charStream){
		delete this->charStream;
	}
	if(this->readStream){
		delete this->readStream;
	}
	if(this->inStream){
		delete this->inStream;
	}
}

CompilationUnit* SmartContractParser::parse() {
	int length = this->file->length();
	this->inStream = new FileInputStream(this->file);

	this->inStream->open();

	this->readStream = new ParserReaderStream(inStream, length);
	this->charStream = new CharStream(readStream);

	this->tokenManager = new AlinousLangTokenManager(charStream);

	this->alinousLang = new AlinousLang(tokenManager);

	return alinousLang->compilationUnit();
}

} /* namespace codablecash */


