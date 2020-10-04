/*
 * AlterRenameTableCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERRENAMETABLECOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERRENAMETABLECOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class UnicodeString;

class AlterRenameTableCommand : public AbstractAlterDdlCommand {
public:
	AlterRenameTableCommand(const AlterRenameTableCommand& inst);
	AlterRenameTableCommand();
	virtual ~AlterRenameTableCommand();

	void setNewName(TableIdentifier* name) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm, AbstractAlterCommandLog* log, TableIdentifier* tableId);

private:
	TableIdentifier* newName;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERRENAMETABLECOMMAND_H_ */
