/*
 * AlterAddIndexCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ALTERADDINDEXCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ALTERADDINDEXCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace alinous {
class AlterAddIndexCommand;
}
using namespace alinous;

namespace codablecash {

class AlterAddIndexCommandLog : public AbstractDdlLog {
public:
	AlterAddIndexCommandLog();
	virtual ~AlterAddIndexCommandLog();

	void setCommand(AlterAddIndexCommand* command) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

private:
	AlterAddIndexCommand* command;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ALTERADDINDEXCOMMANDLOG_H_ */
