/*
 * ScanResultMetadata.h
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCAN_RESULT_SCANRESULTMETADATA_H_
#define TRANSACTION_SCAN_RESULT_SCANRESULTMETADATA_H_

#include "base/HashMap.h"

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class CdbTable;
class CdbTableColumn;
class ScanResultFieldMetadata;

class ScanResultMetadata {
public:
	ScanResultMetadata();
	virtual ~ScanResultMetadata();

private:
	HashMap<UnicodeString, ScanResultFieldMetadata>* map;

};

} /* namespace codablecash */

#endif /* TRANSACTION_SCAN_RESULT_SCANRESULTMETADATA_H_ */
