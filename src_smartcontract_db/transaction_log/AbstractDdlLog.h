/*
 * AbstractDdlLog.h
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ABSTRACTDDLLOG_H_
#define TRANSACTION_LOG_ABSTRACTDDLLOG_H_

#include "transaction_log/AbstractTransactionLog.h"

namespace codablecash {

class AbstractDdlLog : public AbstractTransactionLog {
public:
	explicit AbstractDdlLog(uint8_t type);
	virtual ~AbstractDdlLog();
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ABSTRACTDDLLOG_H_ */
