/*
 * AlterAddPrimaryKeyCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMANDLOG_H_

#include "transaction_log_alter/AbstractAlterCommandLog.h"

namespace alinous {
class AlterAddPrimaryKeyCommand;
}
using namespace alinous;

namespace codablecash {

class AlterAddPrimaryKeyCommandLog : public AbstractAlterCommandLog {
public:
	AlterAddPrimaryKeyCommandLog();
	virtual ~AlterAddPrimaryKeyCommandLog();

	void setCommand(AlterAddPrimaryKeyCommand* command) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm);

private:
	AlterAddPrimaryKeyCommand* command;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMANDLOG_H_ */
