/*
 * TableIdentifier.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_TABLEIDENTIFIER_H_
#define SQL_EXPRESSION_TABLEIDENTIFIER_H_

#include "sql/AbstractJoinPart.h"

namespace alinous {
class UnicodeString;

class TableIdentifier : public AbstractJoinPart {
public:
	TableIdentifier();
	virtual ~TableIdentifier();

	void setSchema(UnicodeString* schema) noexcept;
	void setTableName(UnicodeString* tableName) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
private:
	UnicodeString* schema;
	UnicodeString* tableName;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_TABLEIDENTIFIER_H_ */
