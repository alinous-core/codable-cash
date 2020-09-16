/*
 * AlterAddIndexCommand.h
 *
 *  Created on: 2020/09/08
 *      Author: iizuka
 */

#ifndef SQL_DDL_ALTER_ALTERADDINDEXCOMMAND_H_
#define SQL_DDL_ALTER_ALTERADDINDEXCOMMAND_H_

#include "sql_ddl_alter/AbstractAlterDdlCommand.h"

#include "base/ArrayList.h"

namespace alinous {

class UnicodeString;

class AlterAddIndexCommand : public AbstractAlterDdlCommand {
public:
	AlterAddIndexCommand(const AlterAddIndexCommand& inst);
	AlterAddIndexCommand();
	virtual ~AlterAddIndexCommand();

	void setName(UnicodeString* name) noexcept;
	void addColumn(UnicodeString* colName) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AbstractAlterCommandLog* getCommandLog();

private:
	UnicodeString* name;
	ArrayList<UnicodeString> list;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_ALTERADDINDEXCOMMAND_H_ */
