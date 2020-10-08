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

	virtual void reanalyze(AnalyzeContext* actx, CodeElement* parent);
	virtual void initCommandParam(VirtualMachine* vm, TableIdentifier* tableId);

	AlterModifyCommand* getCommand() const noexcept {
		return command;
	}

	void setLength(int64_t length) noexcept;

	/*const UnicodeString* getDefaultValueStr() const noexcept {
		return defaultValueStr;
	}*/

private:
	AlterModifyCommand* command;

	int64_t length;
};

} /* namespace codablecash */

#endif /* TRANSACTION_LOG_ALTER_MODIFY_ALTERMODIFYCOMMANDLOG_H_ */
