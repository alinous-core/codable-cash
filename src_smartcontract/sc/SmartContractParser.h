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

namespace codablecash {
using namespace alinous;
using namespace alinouslang;

class CompilationUnit;
class ParserReaderStream;
class ParseErrorHandler;

class SmartContractParser {
public:
	explicit SmartContractParser(const File* file);
	virtual ~SmartContractParser();

	CompilationUnit* parse();
	bool hasError() const noexcept;
private:
	File* file;
	FileInputStream* inStream;
	ParserReaderStream* readStream;
	CharStream* charStream;
	AlinousLangTokenManager* tokenManager;
	AlinousLang* alinousLang;

	ParseErrorHandler* parserHandler;
};

} /* namespace codablecash */

#endif /* SC_SMARTCONTRACTPARSER_H_ */
