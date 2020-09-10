/*
 * AlterDropPrimaryKeyCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

class AlterDropPrimaryKeyCommandLog : public AbstractDdlLog {
public:
	AlterDropPrimaryKeyCommandLog();
	virtual ~AlterDropPrimaryKeyCommandLog();
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMANDLOG_H_ */
