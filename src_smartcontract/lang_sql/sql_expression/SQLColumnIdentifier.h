/*
 * SQLColumnIdentifier.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_
#define SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_

#include "lang_sql/sql/AbstractSQLExpression.h"

namespace alinous {
class UnicodeString;

class SQLColumnIdentifier : public AbstractSQLExpression {
public:
	SQLColumnIdentifier();
	SQLColumnIdentifier(const wchar_t* schema, const wchar_t* table, const wchar_t* column);
	virtual ~SQLColumnIdentifier();

	void setSchema(UnicodeString* schema) noexcept;
	void setTableName(UnicodeString* tableName) noexcept;
	void setColumnName(UnicodeString* columnName) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
	virtual void onSelectTarget(VirtualMachine* vm);

	const UnicodeString* getColumnName() const noexcept {
		return columnName;
	}

	const UnicodeString* getSchema() const noexcept {
		return schema;
	}

	const UnicodeString* getTableName() const noexcept {
		return tableName;
	}

private:
	UnicodeString* schema;
	UnicodeString* tableName;
	UnicodeString* columnName;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLCOLUMNIDENTIFIER_H_ */
