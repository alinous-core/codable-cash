/*
 * AlterAddColumnCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_

#include "transaction_log/AbstractDdlLog.h"

namespace alinous {
class AlterAddColumnCommand;
}
using namespace alinous;

namespace codablecash {

class AlterAddColumnCommandLog : public AbstractDdlLog {
public:
	AlterAddColumnCommandLog();
	virtual ~AlterAddColumnCommandLog();

	void setCommand(AlterAddColumnCommand* command) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

private:
	AlterAddColumnCommand* command;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_ */
