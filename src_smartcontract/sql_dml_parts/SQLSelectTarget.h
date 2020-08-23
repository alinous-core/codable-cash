/*
 * SQLSelectTarget.h
 *
 *  Created on: 2019/02/23
 *      Author: iizuka
 */

#ifndef SQL_DML_PARTS_SQLSELECTTARGET_H_
#define SQL_DML_PARTS_SQLSELECTTARGET_H_
#include "sql/AbstractSQLPart.h"

namespace alinous {
class AbstractSQLExpression;
class UnicodeString;
class AnalyzeContext;
class VirtualMachine;
class AbstractVmInstance;

class SQLSelectTarget : public AbstractSQLPart {
public:
	SQLSelectTarget();
	virtual ~SQLSelectTarget();

	void setWildcard(bool wildcard) noexcept;
	void setExpression(AbstractSQLExpression* exp) noexcept;
	void setAsName(UnicodeString* asName)noexcept;

	void preAnalyze(AnalyzeContext* actx);
	void analyzeTypeRef(AnalyzeContext* actx);
	void analyze(AnalyzeContext* actx);

	void init(VirtualMachine* vm);
	AbstractVmInstance* interpret(VirtualMachine* vm);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	const UnicodeString* getAsName() const noexcept {
		return asName;
	}

private:
	bool wildcard;
	AbstractSQLExpression* exp;
	UnicodeString* asName;
};

} /* namespace alinous */

#endif /* SQL_DML_PARTS_SQLSELECTTARGET_H_ */
