/*
 * JsonArrayExpression.h
 *
 *  Created on: 2020/06/28
 *      Author: iizuka
 */

#ifndef SC_EXPRESSION_JSON_JSONARRAYEXPRESSION_H_
#define SC_EXPRESSION_JSON_JSONARRAYEXPRESSION_H_

#include "sc_expression_json/AbstractJsonExpression.h"

namespace alinous {

class JsonArrayExpression : public AbstractJsonExpression {
public:
	JsonArrayExpression();
	virtual ~JsonArrayExpression();

	virtual void preAnalyze(AnalyzeContext* actx);
	virtual void analyzeTypeRef(AnalyzeContext* actx);
	virtual void analyze(AnalyzeContext* actx);
	virtual AnalyzedType getType(AnalyzeContext* actx);

	virtual void init(VirtualMachine* vm);
	virtual AbstractVmInstance* interpret(VirtualMachine* vm);

	virtual int binarySize() const;
	virtual void toBinary(ByteBuffer* out);
	virtual void fromBinary(ByteBuffer* in);
};

} /* namespace alinous */

#endif /* SC_EXPRESSION_JSON_JSONARRAYEXPRESSION_H_ */
