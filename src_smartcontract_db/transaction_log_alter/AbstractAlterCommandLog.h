/*
 * AbstractAlterCommandLog.h
 *
 *  Created on: 2020/09/16
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

class AbstractAlterCommandLog : public AbstractDdlLog {
public:
	AbstractAlterCommandLog(uint8_t type);
	virtual ~AbstractAlterCommandLog();
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ABSTRACTALTERCOMMANDLOG_H_ */
