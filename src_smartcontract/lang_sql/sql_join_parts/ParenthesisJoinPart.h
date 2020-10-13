/*
 * ParenthesisJoinPart.h
 *
 *  Created on: 2019/02/28
 *      Author: iizuka
 */

#ifndef SQL_JOIN_PARTS_PARENTHESISJOINPART_H_
#define SQL_JOIN_PARTS_PARENTHESISJOINPART_H_

#include "lang_sql/sql/AbstractJoinPart.h"

namespace alinous {

class ParenthesisJoinPart : public AbstractJoinPart {
public:
	ParenthesisJoinPart();
	virtual ~ParenthesisJoinPart();

	void setPart(AbstractJoinPart* part) noexcept;

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
	AbstractJoinPart* part;
};

} /* namespace alinous */

#endif /* SQL_JOIN_PARTS_PARENTHESISJOINPART_H_ */
