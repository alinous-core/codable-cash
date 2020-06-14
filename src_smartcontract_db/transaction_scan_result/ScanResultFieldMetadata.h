/*
 * ScanResultFieldMetadata.h
 *
 *  Created on: 2020/06/14
 *      Author: iizuka
 */

#ifndef TRANSACTION_SCAN_RESULT_SCANRESULTFIELDMETADATA_H_
#define TRANSACTION_SCAN_RESULT_SCANRESULTFIELDMETADATA_H_

namespace alinous {
class UnicodeString;
}
using namespace alinous;

namespace codablecash {

class CdbTable;
class CdbTableColumn;

class ScanResultFieldMetadata {
public:
	ScanResultFieldMetadata();
	virtual ~ScanResultFieldMetadata();

private:
	int position;
	CdbTable* table;
	CdbTableColumn* column;

	UnicodeString* asName;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCAN_RESULT_SCANRESULTFIELDMETADATA_H_ */
