/*
 * AlterAddPrimaryKeyCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

class AlterAddPrimaryKeyCommandLog : public AbstractDdlLog {
public:
	AlterAddPrimaryKeyCommandLog();
	virtual ~AlterAddPrimaryKeyCommandLog();
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMANDLOG_H_ */
