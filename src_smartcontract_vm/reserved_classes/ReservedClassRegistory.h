/*
 * ReservedClassRegistory.h
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#ifndef RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_
#define RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_

#include "base/ArrayList.h"
#include "base/HashMap.h"

namespace alinous {
class AnalyzedClass;
class CompilationUnit;
class UnicodeString;

class ReservedClassRegistory {
public:
	ReservedClassRegistory();
	virtual ~ReservedClassRegistory();

	const ArrayList<AnalyzedClass>* getReservedClassesList() const noexcept;
	CompilationUnit* getUnit() const noexcept;

	AnalyzedClass* getAnalyzedClass(const UnicodeString* fqn) const noexcept;

private:
	void addAnalyzedClass(AnalyzedClass* aclass) noexcept;

private:
	ArrayList<AnalyzedClass> list;
	HashMap<UnicodeString, AnalyzedClass> map;
	CompilationUnit* unit;
};

} /* namespace alinous */

#endif /* RESERVED_CLASSES_RESERVEDCLASSREGISTORY_H_ */
