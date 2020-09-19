/*
 * AlterDropColumnCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ALTERDROPCOLUMNCOMMAND_H_
#define SQL_DDL_ALTER_ALTERDROPCOLUMNCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

namespace alinous {

class AlterDropColumnCommand : public AbstractAlterDdlCommand {
public:
	AlterDropColumnCommand(const AlterDropColumnCommand& inst);
	AlterDropColumnCommand();
	virtual ~AlterDropColumnCommand();

	void setName(UnicodeString* name) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual void interpret(VirtualMachine* vm);

private:
	UnicodeString* name;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ALTERDROPCOLUMNCOMMAND_H_ */
