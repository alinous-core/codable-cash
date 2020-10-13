/*
 * IndexScanner.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_INDEXSCANNER_H_
#define SCAN_INDEXSCANNER_H_

#include "scan_select/scan/RangeChecker.h"

namespace alinous {
class BtreeScanner;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbKey;
class IndexStore;
class CdbOidValueList;
class CdbOidValueListCursor;
class CdbOid;

class IndexScanner : public RangeChecker {
public:
	IndexScanner(const CdbRecordKey* begin, bool beginEq, const CdbRecordKey* end, bool endEq, IndexStore* store);
	virtual ~IndexScanner();

	void start();
	void shutdown() noexcept;

	bool hasNext();
	const CdbOid* next();
private:
	bool __hasNext();
private:
	IndexStore* store;
	BtreeScanner* scanner;
	CdbOidValueListCursor* cursor;

	const CdbOid* nextObj;
};

} /* namespace codablecash */

#endif /* SCAN_INDEXSCANNER_H_ */
