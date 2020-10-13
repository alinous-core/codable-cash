/*
 * RecordScanner.h
 *
 *  Created on: 2020/06/11
 *      Author: iizuka
 */

#ifndef SCAN_RECORDSCANNER_H_
#define SCAN_RECORDSCANNER_H_

#include "scan_select/scan/AbstractRecordScanner.h"

namespace alinous {
class BtreeScanner;
}
using namespace alinous;

namespace codablecash {
class TableStore;

class RecordScanner : public AbstractRecordScanner {
public:
	explicit RecordScanner(TableStore* tableStore);
	virtual ~RecordScanner();

	virtual void start();
	virtual void shutdown() noexcept;

	virtual bool hasNext();
	virtual const CdbRecord* next();
private:
	TableStore* tableStore;
	BtreeScanner* scanner;
};

} /* namespace codablecash */

#endif /* SCAN_RECORDSCANNER_H_ */
