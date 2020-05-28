/*
 * InsertLog.h
 *
 *  Created on: 2020/05/28
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_INSERTLOG_H_
#define TRANSACTION_LOG_INSERTLOG_H_

#include "transaction_log/AbstractTransactionLog.h"

namespace codablecash {

class InsertLog : public AbstractTransactionLog {
public:
	InsertLog();
	virtual ~InsertLog();
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_INSERTLOG_H_ */
