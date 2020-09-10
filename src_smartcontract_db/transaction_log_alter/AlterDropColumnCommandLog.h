/*
 * AlterDropColumnCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ALTERDROPCOLUMNCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ALTERDROPCOLUMNCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace codablecash {

class AlterDropColumnCommandLog : public AbstractDdlLog {
public:
	AlterDropColumnCommandLog();
	virtual ~AlterDropColumnCommandLog();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ALTERDROPCOLUMNCOMMANDLOG_H_ */
