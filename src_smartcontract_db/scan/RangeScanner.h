/*
 * RangeScanner.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_RANGESCANNER_H_
#define SCAN_RANGESCANNER_H_

#include "scan/AbstractRecordScanner.h"

namespace alinous {
class AbstractBtreeKey;

}
using namespace alinous;

namespace codablecash {

class AbstractCdbKey;


class RangeScanner : public AbstractRecordScanner {
public:
	RangeScanner(const AbstractCdbKey* begin, bool beginEq, const AbstractCdbKey* end, bool endEq);
	virtual ~RangeScanner();

	AbstractBtreeKey* getFirstScanKey() const noexcept;
private:
	AbstractBtreeKey* begin;
	bool beginEq;
	AbstractBtreeKey* end;
	bool endEq;
};

} /* namespace codablecash */

#endif /* SCAN_RANGESCANNER_H_ */