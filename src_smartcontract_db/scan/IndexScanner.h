/*
 * IndexScanner.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_INDEXSCANNER_H_
#define SCAN_INDEXSCANNER_H_

#include "scan/RangeScanner.h"

namespace codablecash {

class AbstractCdbKey;

class IndexScanner : public RangeScanner {
public:
	IndexScanner(AbstractCdbKey* begin, bool beginEq, AbstractCdbKey* end, bool endEq);
	virtual ~IndexScanner();


};

} /* namespace codablecash */

#endif /* SCAN_INDEXSCANNER_H_ */
