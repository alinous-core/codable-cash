/*
 * AllocationExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_ALLOCATIONEXPRESSION_H_
#define SC_EXPRESSION_ALLOCATIONEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"

namespace alinous {
class PackageNameDeclare;
class ConstructorCall;
class ConstructorArray;
class AnalyzedType;

class AllocationExpression : public AbstractExpression {
public:
	AllocationExpression();
	virtual ~AllocationExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void setPackage(PackageNameDeclare* packageName) noexcept;
	void setExpression(ConstructorCall* exp) noexcept;
	void setConstructorArray(ConstructorArray* array) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

private:
	void analyzeArray(AnalyzeContext* actx);
	AnalyzedType* findType(AnalyzeContext* actx, const UnicodeString* className) const;
	AbstractVmInstance* interpretArray(VirtualMachine* vm);
private:
	PackageNameDeclare* packageName;
	ConstructorCall* constructorCall;
	ConstructorArray* array;

};

} /* namespace alinous */

#endif /* SC_EXPRESSION_ALLOCATIONEXPRESSION_H_ */
