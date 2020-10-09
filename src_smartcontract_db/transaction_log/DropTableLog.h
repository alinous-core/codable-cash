/*
 * DropTableLog.h
 *
 *  Created on: 2020/10/09
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_DROPTABLELOG_H_
#define TRANSACTION_LOG_DROPTABLELOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace alinous {
class TableIdentifier;
}
using namespace alinous;

namespace codablecash {

class DropTableLog : public AbstractDdlLog {
public:
	DropTableLog();
	virtual ~DropTableLog();

private:
	TableIdentifier* tableId;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_DROPTABLELOG_H_ */
