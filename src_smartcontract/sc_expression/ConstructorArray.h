/*
 * ConstructorArray.h
 *
 *  Created on: 2020/02/12
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_CONSTRUCTORARRAY_H_
#define SC_EXPRESSION_CONSTRUCTORARRAY_H_

#include "sc_expression/AbstractExpression.h"
#include "base/ArrayList.h"

namespace alinous {

class VariableIdentifier;
class NumberLiteral;

class ConstructorArray : public AbstractExpression {
public:
	ConstructorArray();
	virtual ~ConstructorArray();

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

	void setValId(VariableIdentifier* valId) noexcept;
	void addDim(NumberLiteral* dim) noexcept;

	const UnicodeString* getName() const noexcept;
private:
	VariableIdentifier* valId;
	ArrayList<NumberLiteral> dims;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_CONSTRUCTORARRAY_H_ */
