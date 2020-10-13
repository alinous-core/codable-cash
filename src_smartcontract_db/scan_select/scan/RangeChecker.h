/*
 * RangeScanner.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_RANGECHECKER_H_
#define SCAN_RANGECHECKER_H_

#include "scan_select/scan/AbstractRecordScanner.h"

namespace alinous {
class AbstractBtreeKey;

}
using namespace alinous;

namespace codablecash {

class CdbRecordKey;


class RangeChecker {
public:
	RangeChecker(const CdbRecordKey* begin, bool beginEq, const CdbRecordKey* end, bool endEq);
	virtual ~RangeChecker();

	AbstractBtreeKey* getFirstScanKey() const noexcept;

	bool checkLowerBound(const CdbRecordKey* key) const noexcept;
	bool checkUpperBound(const CdbRecordKey* key) const noexcept;

private:
	CdbRecordKey* begin;
	bool beginEq;
	CdbRecordKey* end;
	bool endEq;
};

} /* namespace codablecash */

#endif /* SCAN_RANGECHECKER_H_ */
