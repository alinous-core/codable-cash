/*
 * MemberVariableTable.h
 *
 *  Created on: 2020/01/04
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_VARIABLES_MEMBERVARIABLETABLE_H_
#define SC_ANALYZE_VARIABLES_MEMBERVARIABLETABLE_H_

#include "base/ArrayList.h"
#include "base/HashMap.h"


namespace alinous {

class MemberVariableEntry;
class MemberVariableDeclare;

class MemberVariableTable {
public:
	MemberVariableTable();
	virtual ~MemberVariableTable();

	void addEntry(const UnicodeString* name, MemberVariableDeclare* dec) noexcept;
	bool hasEntry(const UnicodeString* name) const noexcept;

	ArrayList<MemberVariableEntry>* getVariableList() noexcept;
private:
	ArrayList<MemberVariableEntry> list;
	HashMap<UnicodeString, MemberVariableEntry> map;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_VARIABLES_MEMBERVARIABLETABLE_H_ */
