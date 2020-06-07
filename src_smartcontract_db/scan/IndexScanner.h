/*
 * IndexScanner.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_INDEXSCANNER_H_
#define SCAN_INDEXSCANNER_H_

#include "scan/RangeScanner.h"

namespace alinous {
class BtreeScanner;
}
using namespace alinous;

namespace codablecash {

class AbstractCdbKey;
class IndexStore;


class IndexScanner : public RangeScanner {
public:
	IndexScanner(AbstractCdbKey* begin, bool beginEq, AbstractCdbKey* end, bool endEq, IndexStore* store);
	virtual ~IndexScanner();

	virtual void start();
	virtual bool hasNext();

private:
	IndexStore* store;
	BtreeScanner* scanner;
};

} /* namespace codablecash */

#endif /* SCAN_INDEXSCANNER_H_ */
