/*
 * AlterAddColumnCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_
#define SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class DdlColumnDescriptor;

class AlterAddColumnCommand : public AbstractAlterDdlCommand {
public:
	AlterAddColumnCommand(const AlterAddColumnCommand& inst);
	AlterAddColumnCommand();
	virtual ~AlterAddColumnCommand();

	void setColumnDescriptor(DdlColumnDescriptor* columnDescriptor) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm, AbstractAlterCommandLog* log);

private:
	DdlColumnDescriptor* columnDescriptor;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ALTERADDCOLUMNCOMMAND_H_ */
