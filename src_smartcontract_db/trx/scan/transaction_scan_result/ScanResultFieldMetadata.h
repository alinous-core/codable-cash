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
	ScanResultFieldMetadata(const ScanResultFieldMetadata& inst);

	ScanResultFieldMetadata(const CdbTable* table, const CdbTableColumn* column);
	virtual ~ScanResultFieldMetadata();

	void setPosition(int pos) noexcept;
private:
	int position;
	const CdbTable* table;
	const CdbTableColumn* column;

	UnicodeString* asName;
	bool use;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCAN_RESULT_SCANRESULTFIELDMETADATA_H_ */
