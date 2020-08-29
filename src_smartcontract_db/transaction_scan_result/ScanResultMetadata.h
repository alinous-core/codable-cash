/*
 * ScanResultMetadata.h
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCAN_RESULT_SCANRESULTMETADATA_H_
#define TRANSACTION_SCAN_RESULT_SCANRESULTMETADATA_H_

#include "base/ArrayList.h"


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
	ScanResultMetadata(const ScanResultMetadata& inst);
	ScanResultMetadata();
	virtual ~ScanResultMetadata();

	void addField(const ScanResultFieldMetadata* fld) noexcept;

private:
	ArrayList<ScanResultFieldMetadata> *list;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCAN_RESULT_SCANRESULTMETADATA_H_ */
