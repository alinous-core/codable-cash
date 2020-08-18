/*
 * IndexRecordScanner.h
 *
 *  Created on: 2020/08/18
 *      Author: iizuka
 */

#ifndef SCAN_INDEXRECORDSCANNER_H_
#define SCAN_INDEXRECORDSCANNER_H_

#include "scan/AbstractRecordScanner.h"

namespace codablecash {

class IndexRecordScanner : public AbstractRecordScanner {
public:
	IndexRecordScanner();
	virtual ~IndexRecordScanner();

	virtual void start();
	virtual void shutdown() noexcept;
	virtual bool hasNext();
	virtual const CdbRecord* next();
};

} /* namespace codablecash */

#endif /* SCAN_INDEXRECORDSCANNER_H_ */
