/*
 * AlterDropIndexCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ALTERDROPINDEXCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ALTERDROPINDEXCOMMANDLOG_H_

#include "trx/transaction_log_alter/AbstractAlterCommandLog.h"

namespace alinous {
class AlterDropIndexCommand;
}
using namespace alinous;

namespace codablecash {

class AlterDropIndexCommandLog : public AbstractAlterCommandLog {
public:
	AlterDropIndexCommandLog();
	virtual ~AlterDropIndexCommandLog();

	void setCommand(AlterDropIndexCommand* command) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

	virtual void initCommandParam(VirtualMachine* vm, TableIdentifier* tableId);

	const AlterDropIndexCommand* getCommand() const noexcept {
		return command;
	}

private:
	AlterDropIndexCommand* command;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ALTERDROPINDEXCOMMANDLOG_H_ */
