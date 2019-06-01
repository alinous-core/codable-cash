/*
 * AnalyzedClass.h
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZEDCLASS_H_
#define SC_ANALYZE_ANALYZEDCLASS_H_

#include "base/HashMap.h"


namespace alinous {

class ClassDeclare;
class UnicodeString;
class MemberVariableDeclare;

class AnalyzedClass {
public:
	explicit AnalyzedClass(ClassDeclare* clazz);
	virtual ~AnalyzedClass();

	void addMemberVariableDeclare(MemberVariableDeclare* member);

private:
	ClassDeclare* clazz;

	HashMap<UnicodeString, MemberVariableDeclare>* variables;

};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZEDCLASS_H_ */
