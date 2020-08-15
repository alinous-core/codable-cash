/*
 * RangeScanner.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_RANGECHECKER_H_
#define SCAN_RANGECHECKER_H_

#include "scan/AbstractRecordScanner.h"

namespace alinous {
class AbstractBtreeKey;

}
using namespace alinous;

namespace codablecash {

class AbstractCdbKey;


class RangeChecker {
public:
	RangeChecker(const AbstractCdbKey* begin, bool beginEq, const AbstractCdbKey* end, bool endEq);
	virtual ~RangeChecker();

	AbstractBtreeKey* getFirstScanKey() const noexcept;

	bool checkLower(const AbstractCdbKey* key) const noexcept;
	bool checkUpper(const AbstractCdbKey* key) const noexcept;

private:
	AbstractBtreeKey* begin;
	bool beginEq;
	AbstractBtreeKey* end;
	bool endEq;
};

} /* namespace codablecash */

#endif /* SCAN_RANGECHECKER_H_ */
