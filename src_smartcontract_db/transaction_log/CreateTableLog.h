/*
 * CreateTableLog.h
 *
 *  Created on: 2020/05/12
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_CREATETABLELOG_H_
#define TRANSACTION_LOG_CREATETABLELOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

class CreateTableLog : public AbstractDdlLog {
public:
	CreateTableLog();
	virtual ~CreateTableLog();
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_CREATETABLELOG_H_ */
