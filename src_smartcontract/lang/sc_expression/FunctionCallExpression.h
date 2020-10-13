/*
 * FunctionCallExpression.h
 *
 *  Created on: 2019/02/05
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_FUNCTIONCALLEXPRESSION_H_
#define SC_EXPRESSION_FUNCTIONCALLEXPRESSION_H_

#include "lang/sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {
class UnicodeString;
class VTableMethodEntry;
class StackVariableAccess;
class FunctionArguments;
class AnalyzedClass;
class VmClassInstance;
class VariableIdentifier;
class StackFloatingVariableHandler;
class AbstractVariableInstraction;
class MethodDeclare;

class FunctionCallExpression : public AbstractExpression {
public:
	FunctionCallExpression();
	virtual ~FunctionCallExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);

	void analyze(AnalyzeContext* actx, AnalyzedClass* athisClass, AbstractVariableInstraction* lastIinst);

	void setName(AbstractExpression* exp) noexcept;
	VariableIdentifier* getName() const noexcept;

	void addArgument(AbstractExpression* exp) noexcept;

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);
	AbstractVmInstance* interpret(VirtualMachine* vm, VmClassInstance* classInst);

	bool isSuperConstructorCall() const noexcept;
private:
	void analyzeArguments(AnalyzeContext* actx);
	void analyzeMethodEntry(AnalyzeContext* actx, AnalyzedClass* athisClass, bool staticMode);
	void analyzeSuperConstructorEntry(AnalyzeContext* actx);
	bool isOnConstructor() const noexcept;

	AbstractVmInstance* interpretStatic(VirtualMachine* vm, VmClassInstance* classInst, MethodDeclare* methodDeclare);
	AbstractVmInstance* interpretVirtual(VirtualMachine* vm, FunctionArguments* args);
	void interpretThisPointer(VirtualMachine* vm, FunctionArguments* args);
	void interpretArguments(VirtualMachine* vm, FunctionArguments* args, StackFloatingVariableHandler* releaser);
private:
	AbstractExpression* name;
	ArrayList<AbstractExpression> args;

	UnicodeString* strName;
	VTableMethodEntry* methodEntry;
	const UnicodeString* callSignature;

	StackVariableAccess* thisAccess;
	bool noVirtual;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_FUNCTIONCALLEXPRESSION_H_ */
