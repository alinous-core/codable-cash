/*
 * AlterAddColumnCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_

#include "transaction_log_alter/AbstractAlterCommandLog.h"

namespace alinous {
class AlterAddColumnCommand;
}
using namespace alinous;

namespace codablecash {

class AlterAddColumnCommandLog : public AbstractAlterCommandLog {
public:
	AlterAddColumnCommandLog();
	virtual ~AlterAddColumnCommandLog();

	void setCommand(AlterAddColumnCommand* command) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

	virtual void reanalyze(AnalyzeContext* ctx, CodeElement* parent);
	virtual void initCommandParam(VirtualMachine* vm, TableIdentifier* tableId);

	AlterAddColumnCommand* getCommand() const noexcept {
		return command;
	}

private:
	AlterAddColumnCommand* command;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_ALTERADDCOLUMNCOMMANDLOG_H_ */
