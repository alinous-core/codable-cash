/*
 * AlterAddColumnCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

class AlterAddColumnCommandLog: public AbstractDdlLog {
public:
	AlterAddColumnCommandLog();
	virtual ~AlterAddColumnCommandLog();
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_ */
