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
}


namespace codablecash {
using namespace alinous;

class SmartContractParser {
public:
	explicit SmartContractParser(const File* file);
	virtual ~SmartContractParser();

	void parse();
private:
	File* file;
};

} /* namespace codablecash */

#endif /* SC_SMARTCONTRACTPARSER_H_ */
