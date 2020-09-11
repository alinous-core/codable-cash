/*
 * AlterRenameColumnCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace alinous {
class AlterRenameColumnCommand;
}
using namespace alinous;

namespace codablecash {

class AlterRenameColumnCommandLog : public AbstractDdlLog {
public:
	AlterRenameColumnCommandLog();
	virtual ~AlterRenameColumnCommandLog();

	void setCommand(AlterRenameColumnCommand* command) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

private:
	AlterRenameColumnCommand* command;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMANDLOG_H_ */
