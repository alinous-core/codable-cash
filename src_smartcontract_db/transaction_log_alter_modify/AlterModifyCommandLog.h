/*
 * AlterModifyCommandLog.h
 *
 *  Created on: 2020/09/10
 *      Author: iizuka
 */

#ifndef TRANSACTION_LOG_ALTER_MODIFY_ALTERMODIFYCOMMANDLOG_H_
#define TRANSACTION_LOG_ALTER_MODIFY_ALTERMODIFYCOMMANDLOG_H_

#include "transaction_log_alter/AbstractAlterCommandLog.h"

namespace alinous {
class AlterModifyCommand;
}
using namespace alinous;

namespace codablecash {

class AlterModifyCommandLog : public AbstractAlterCommandLog {
public:
	AlterModifyCommandLog();
	virtual ~AlterModifyCommandLog();

	void setCommand(AlterModifyCommand* command) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out) const;
	virtual void fromBinary(ByteBuffer* in);

	virtual void commit(CdbTransactionManager* trxManager);

	const AlterModifyCommand* getCommand() const noexcept {
		return command;
	}

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm);

private:
	AlterModifyCommand* command;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_MODIFY_ALTERMODIFYCOMMANDLOG_H_ */
