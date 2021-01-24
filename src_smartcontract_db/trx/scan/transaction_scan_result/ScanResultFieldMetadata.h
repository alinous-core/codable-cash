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

class AbstractScanTableTarget;
class CdbTableColumn;
class ColumnIdentifierScanParam;

class ScanResultFieldMetadata {
public:
	ScanResultFieldMetadata(const ScanResultFieldMetadata& inst);

	ScanResultFieldMetadata(const AbstractScanTableTarget* sourceTarget, const CdbTableColumn* column);
	virtual ~ScanResultFieldMetadata();

	void setPosition(int pos) noexcept;
	int getPosition() const noexcept {
		return position;
	}

	bool match(ColumnIdentifierScanParam* scanColumnId) const noexcept;

private:
	int position; // position in scanned metadata, not in the table
	const AbstractScanTableTarget* sourceTarget;
	const CdbTableColumn* column;

	UnicodeString* asName;
	bool use;
};

} /* namespace codablecash */

#endif /* TRANSACTION_SCAN_RESULT_SCANRESULTFIELDMETADATA_H_ */
