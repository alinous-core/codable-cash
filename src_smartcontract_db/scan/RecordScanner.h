/*
 * RecordScanner.h
 *
 *  Created on: 2020/06/11
 *      Author: iizuka
 */

#ifndef SCAN_RECORDSCANNER_H_
#define SCAN_RECORDSCANNER_H_

#include "scan/AbstractRecordScanner.h"

namespace codablecash {

class TableStore;

class RecordScanner : public AbstractRecordScanner {
public:
	RecordScanner(TableStore* tableStore);
	virtual ~RecordScanner();

	virtual void start();

private:
	TableStore* tableStore;
};

} /* namespace codablecash */

#endif /* SCAN_RECORDSCANNER_H_ */
