/*
 * CreateTableStatement.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_DDL_CREATETABLESTATEMENT_H_
#define SQL_DDL_CREATETABLESTATEMENT_H_

#include "lang_sql/sql/AbstractSQLStatement.h"

#include "base/ArrayList.h"

namespace codablecash {
class CdbTable;
class CreateTableLog;
}
using namespace codablecash;

namespace alinous {

class DdlColumnDescriptor;

class CreateTableStatement : public AbstractSQLStatement {
public:
	CreateTableStatement();
	virtual ~CreateTableStatement();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void interpret(VirtualMachine* vm);

	void setName(UnicodeString* name) noexcept;
	void addColumn(DdlColumnDescriptor* col) noexcept;
	void addPrimaryKey(UnicodeString* key) noexcept;

private:
	void validate(VirtualMachine* vm, CreateTableLog* cmd);
	CdbTable* createTable(VirtualMachine* vm);
private:
	UnicodeString* name;
	ArrayList<DdlColumnDescriptor>* list;
	ArrayList<UnicodeString>* primaryKeys;
};

} /* namespace alinous */

#endif /* SQL_DDL_CREATETABLESTATEMENT_H_ */
