/*
 * AbstractRecordScanner.h
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#ifndef SCAN_ABSTRACTRECORDSCANNER_H_
#define SCAN_ABSTRACTRECORDSCANNER_H_

namespace codablecash {

class CdbRecord;

class AbstractRecordScanner {
public:
	AbstractRecordScanner();
	virtual ~AbstractRecordScanner();

	virtual void start() = 0;
	virtual void shutdown() noexcept = 0;
	virtual bool hasNext() = 0;
	virtual const CdbRecord* next() = 0;
};

} /* namespace codablecash */

#endif /* SCAN_ABSTRACTRECORDSCANNER_H_ */
