/*
 * IndexScanner.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_INDEXSCANNER_H_
#define SCAN_INDEXSCANNER_H_

#include "scan/AbstractRecordScanner.h"

namespace codablecash {

class AbstractCdbKey;

class IndexScanner : public AbstractRecordScanner {
public:
	IndexScanner(AbstractCdbKey* begin, bool beginEq, AbstractCdbKey* end, bool endEq);
	virtual ~IndexScanner();

private:
	AbstractCdbKey* begin;
	bool beginEq;
	AbstractCdbKey* end;
	bool endEq;
};

} /* namespace codablecash */

#endif /* SCAN_INDEXSCANNER_H_ */
