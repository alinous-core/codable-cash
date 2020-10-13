/*
 * SQLLiteral.h
 *
 *  Created on: 2019/02/16
 *      Author: iizuka
 */

#ifndef SQL_EXPRESSION_SQLLITERAL_H_
#define SQL_EXPRESSION_SQLLITERAL_H_

#include "lang_sql/sql/AbstractSQLExpression.h"
#include <cstdint>

namespace alinous {
class UnicodeString;

class SQLLiteral : public AbstractSQLExpression {
public:
	static const constexpr uint8_t TYPE_STRING{1};
	static const constexpr uint8_t TYPE_NUMBER{2};

	SQLLiteral();
	virtual ~SQLLiteral();

	void setValue(UnicodeString* value, uint8_t type) noexcept;
	uint8_t getLiteralType() const noexcept {
		return this->type;
	}

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

	int64_t getLongv() const noexcept {
		return longv;
	}

private:
	void interpretOnPlanning(VirtualMachine* vm);
private:
	UnicodeString* value;
	uint8_t type;

	int64_t longv;
	UnicodeString* stringValue;
};

} /* namespace alinous */

#endif /* SQL_EXPRESSION_SQLLITERAL_H_ */
