/*
 * SmartContractParser.h
 *
 *  Created on: 2019/01/15
 *      Author: iizuka
 */

#ifndef SC_PARSER_SMARTCONTRACTPARSER_H_
#define SC_PARSER_SMARTCONTRACTPARSER_H_

namespace alinous {
class File;
}


namespace codablecash {
using namespace alinous;


class SmartContractParser {
public:
	SmartContractParser();
	virtual ~SmartContractParser();
};

} /* namespace codablecash */

#endif /* SC_PARSER_SMARTCONTRACTPARSER_H_ */
