/*
 * AlterRenameColumnCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterRenameColumnCommand : public AbstractAlterDdlCommand {
public:
	AlterRenameColumnCommand(const AlterRenameColumnCommand& inst);
	AlterRenameColumnCommand();
	virtual ~AlterRenameColumnCommand();

	void setLastName(UnicodeString* name) noexcept;
	void setNewName(UnicodeString* name) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm, AbstractAlterCommandLog* log);

private:
	UnicodeString* lastName;
	UnicodeString* newName;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERRENAMECOLUMNCOMMAND_H_ */
