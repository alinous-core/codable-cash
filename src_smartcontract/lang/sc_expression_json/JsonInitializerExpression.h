/*
 * JsonInitializer.h
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_JSON_JSONINITIALIZEREXPRESSION_H_
#define SC_EXPRESSION_JSON_JSONINITIALIZEREXPRESSION_H_

#include "lang/sc_expression_json/AbstractJsonExpression.h"

#include "base/ArrayList.h"

namespace alinous {

class JsonKeyValuePairExpression;

class JsonInitializerExpression : public AbstractJsonExpression {
public:
	JsonInitializerExpression();
	virtual ~JsonInitializerExpression();

	void addElement(JsonKeyValuePairExpression* element) noexcept;

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);

private:
	ArrayList<JsonKeyValuePairExpression>* elements;
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_JSON_JSONINITIALIZEREXPRESSION_H_ */
