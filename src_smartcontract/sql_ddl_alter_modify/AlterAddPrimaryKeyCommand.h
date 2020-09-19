/*
 * AlterAddPrimaryKeyCommand.h
 *
 *  Created on: 2020/09/09
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMAND_H_
#define SQL_DDL_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

#include "base/ArrayList.h"

namespace alinous {

class UnicodeString;

class AlterAddPrimaryKeyCommand : public AbstractAlterDdlCommand {
public:
	AlterAddPrimaryKeyCommand(const AlterAddPrimaryKeyCommand& inst);
	AlterAddPrimaryKeyCommand();
	virtual ~AlterAddPrimaryKeyCommand();

	void addColumn(UnicodeString* column) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm);

private:
	ArrayList<UnicodeString> list;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMAND_H_ */
