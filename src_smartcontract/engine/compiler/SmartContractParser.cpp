/*
 * SmartContractParser.cpp
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#include "engine/compiler/SmartContractParser.h"
#include "engine/compiler/ParserReaderStream.h"
#include "engine/compiler/ParseErrorHandler.h"
#include "engine/compiler/LexErrorHandler.h"

#include "base_io/File.h"
#include "base_io_stream/FileInputStream.h"

#include "alinous_lang/CharStream.h"
#include "alinous_lang/AlinousLangTokenManager.h"
#include "alinous_lang/AlinousLang.h"

namespace alinous {
using namespace alinouslang;

SmartContractParser::SmartContractParser(const File* file) {
	this->file = new File(*file);
	this->length = 0;
	this->inStream = nullptr;
	this->readStream = nullptr;
	this->charStream = nullptr;
	this->tokenManager = nullptr;
	this->alinousLang = nullptr;
	this->parserErrorHandler = nullptr;
	this->lexErrorHandler = nullptr;
}

SmartContractParser::SmartContractParser(InputStream* stream, int length) {
	this->file = nullptr;
	this->length = length;
	this->inStream = stream;
	this->readStream = nullptr;
	this->charStream = nullptr;
	this->tokenManager = nullptr;
	this->alinousLang = nullptr;
	this->parserErrorHandler = nullptr;
	this->lexErrorHandler = nullptr;
}

SmartContractParser::~SmartContractParser() {
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
	if(this->file != nullptr && this->inStream){
		delete this->inStream;
	}

	delete file;
}

AlinousLang* SmartContractParser::getDebugAlinousLang() {
	if(this->inStream == nullptr){
		this->length = this->file->length();
		this->inStream = new FileInputStream(this->file);
	}

	if(!this->inStream->available()){
		this->inStream->open();
	}

	this->readStream = new ParserReaderStream(inStream, length);
	this->charStream = new CharStream(readStream);

	this->tokenManager = new AlinousLangTokenManager(charStream);
	this->lexErrorHandler = new LexErrorHandler();
	this->tokenManager->setErrorHandler(this->lexErrorHandler);

	this->parserErrorHandler = new ParseErrorHandler();
	this->alinousLang = new AlinousLang(tokenManager);
	this->alinousLang->setErrorHandler(this->parserErrorHandler);

	return this->alinousLang;
}

CompilationUnit* SmartContractParser::parse() {
	if(this->inStream == nullptr){
		this->length = this->file->length();
		this->inStream = new FileInputStream(this->file);
	}

	return parseStream();
}

CompilationUnit* SmartContractParser::parseStream() {
	if(!this->inStream->available()){
		this->inStream->open();
	}

	this->readStream = new ParserReaderStream(inStream, length);
	this->charStream = new CharStream(readStream);

	this->tokenManager = new AlinousLangTokenManager(charStream);
	this->lexErrorHandler = new LexErrorHandler();
	this->tokenManager->setErrorHandler(this->lexErrorHandler);

	this->parserErrorHandler = new ParseErrorHandler();
	this->alinousLang = new AlinousLang(tokenManager);
	this->alinousLang->setErrorHandler(this->parserErrorHandler);

	return alinousLang->compilationUnit();
}

bool SmartContractParser::hasError() const noexcept {
	return this->parserErrorHandler != nullptr && this->parserErrorHandler != nullptr &&
			(this->parserErrorHandler->hasError() || this->lexErrorHandler->hasError());
}

bool SmartContractParser::hasLexError() const noexcept {
	return this->parserErrorHandler != nullptr && this->lexErrorHandler->hasError();
}

} /* namespace alinous */


