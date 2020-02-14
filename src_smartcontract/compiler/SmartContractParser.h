/*
 * SmartContractParser.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_SMARTCONTRACTPARSER_H_
#define SC_SMARTCONTRACTPARSER_H_

namespace alinous {
class File;
class FileInputStream;
}

namespace alinouslang {
class CharStream;
class AlinousLangTokenManager;
class AlinousLang;
}

namespace alinous {
using namespace alinouslang;

class CompilationUnit;
class ParserReaderStream;
class ParseErrorHandler;
class LexErrorHandler;
class InputStream;

class SmartContractParser {
public:
	explicit SmartContractParser(const File* file);
	explicit SmartContractParser(InputStream* stream, int length);
	virtual ~SmartContractParser();

	CompilationUnit* parse();
	bool hasError() const noexcept;
	bool hasLexError() const noexcept;

	AlinousLang* getDebugAlinousLang();

	const ParseErrorHandler* getParserErrorHandler() const {
		return parserErrorHandler;
	}

private:
	CompilationUnit* parseStream();
private:
	File* file;
	InputStream* inStream;
	int length;
	ParserReaderStream* readStream;
	CharStream* charStream;
	AlinousLangTokenManager* tokenManager;
	AlinousLang* alinousLang;

	ParseErrorHandler* parserErrorHandler;
	LexErrorHandler* lexErrorHandler;
};

} /* namespace alinous */

#endif /* SC_SMARTCONTRACTPARSER_H_ */
