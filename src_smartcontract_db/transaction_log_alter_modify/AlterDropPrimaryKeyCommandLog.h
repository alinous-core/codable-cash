/*
 * AlterDropPrimaryKeyCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace alinous {
class AlterDropPrimaryKeyCommand;
}
using namespace alinous;

namespace codablecash {

class AlterDropPrimaryKeyCommandLog : public AbstractDdlLog {
public:
	AlterDropPrimaryKeyCommandLog();
	virtual ~AlterDropPrimaryKeyCommandLog();

	void setCommand(AlterDropPrimaryKeyCommand* command) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

private:
	AlterDropPrimaryKeyCommand* command;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_MODIFY_ALTERDROPPRIMARYKEYCOMMANDLOG_H_ */
