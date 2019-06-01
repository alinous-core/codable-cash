/*
 * AnalyzedClass.h
 *
 *  Created on: 2019/06/01
 *      Author: iizuka
 */

#ifndef SC_ANALYZE_ANALYZEDCLASS_H_
#define SC_ANALYZE_ANALYZEDCLASS_H_

namespace alinous {

class ClassDeclare;

class AnalyzedClass {
public:
	explicit AnalyzedClass(ClassDeclare* clazz);
	virtual ~AnalyzedClass();

private:
	ClassDeclare* clazz;


};

} /* namespace alinous */

#endif /* SC_ANALYZE_ANALYZEDCLASS_H_ */
