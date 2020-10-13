/*
 * JsonKeyValuePair.h
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_JSON_JSONKEYVALUEPAIREXPRESSION_H_
#define SC_EXPRESSION_JSON_JSONKEYVALUEPAIREXPRESSION_H_

#include "lang/sc_expression_json/AbstractJsonExpression.h"

namespace alinous {

class LiteralExpression;

class JsonKeyValuePairExpression : public AbstractJsonExpression {
public:
	JsonKeyValuePairExpression();
	virtual ~JsonKeyValuePairExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

	void setName(UnicodeString* name) noexcept;
	void setName(LiteralExpression* name) noexcept;
	void setValue(AbstractExpression* value) noexcept;

	const UnicodeString* getName() const noexcept;
private:
	UnicodeString* name;
	AbstractExpression* value;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_JSON_JSONKEYVALUEPAIREXPRESSION_H_ */
