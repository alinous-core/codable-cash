/*
 * TableList.h
 *
 *  Created on: 2019/02/27
 *      Author: iizuka
 */

#ifndef SQL_JOIN_PARTS_TABLELIST_H_
#define SQL_JOIN_PARTS_TABLELIST_H_

#include "base/ArrayList.h"
#include "lang_sql/sql/AbstractJoinPart.h"

namespace alinous {

class TableIdentifier;

class TableList : public AbstractJoinPart {
public:
	TableList();
	virtual ~TableList();

	void addTable(AbstractJoinPart* tableId) noexcept;

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
	ArrayList<AbstractJoinPart> list;
};

} /* namespace alinous */

#endif /* SQL_JOIN_PARTS_TABLELIST_H_ */
