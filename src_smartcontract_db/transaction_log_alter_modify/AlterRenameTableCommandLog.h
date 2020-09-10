/*
 * AlterRenameTableCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_MODIFY_ALTERRENAMETABLECOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_MODIFY_ALTERRENAMETABLECOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

class AlterRenameTableCommandLog : public AbstractDdlLog {
public:
	AlterRenameTableCommandLog();
	virtual ~AlterRenameTableCommandLog();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_MODIFY_ALTERRENAMETABLECOMMANDLOG_H_ */
