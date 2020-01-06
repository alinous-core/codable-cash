/*
 * MemberVariableEntry.h
 *
 *  Created on: 2020/01/04
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_VARIABLES_MEMBERVARIABLEENTRY_H_
#define SC_ANALYZE_VARIABLES_MEMBERVARIABLEENTRY_H_

namespace alinous {

class UnicodeString;
class MemberVariableDeclare;

class MemberVariableEntry {
public:
	MemberVariableEntry(const UnicodeString* name, MemberVariableDeclare* dec);
	virtual ~MemberVariableEntry();

	const UnicodeString* getName() const noexcept;
	MemberVariableDeclare* getMemberVariableDeclare() const noexcept;
private:
	UnicodeString* name;
	MemberVariableDeclare* dec;
};

} /* namespace alinous */

#endif /* SC_ANALYZE_VARIABLES_MEMBERVARIABLEENTRY_H_ */
