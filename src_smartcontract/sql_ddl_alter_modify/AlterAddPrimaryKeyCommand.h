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
	AlterAddPrimaryKeyCommand();
	virtual ~AlterAddPrimaryKeyCommand();

	void addColumn(UnicodeString* column) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

private:
	ArrayList<UnicodeString> list;
};

} /* namespace alinous */

#endif /* SQL_DDL_ALTER_MODIFY_ALTERADDPRIMARYKEYCOMMAND_H_ */
