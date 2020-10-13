/*
 * ReservedClassRegistory.cpp
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#include "instance/reserved_classes/ReservedClassRegistory.h"

#include "engine/sc_analyze/AnalyzedClass.h"

#include "instance/reserved_classes_string/StringClassDeclare.h"

#include "instance/instance_exception_class/ExceptionClassDeclare.h"

#include "engine/sc/CompilationUnit.h"

#include "instance/instance_exception/ArrayOutOfBoundsExceptionClassDeclare.h"
#include "instance/instance_exception/NullPointerExceptionClassDeclare.h"
#include "instance/instance_exception/ZeroDivisionExceptionClassDeclare.h"
#include "instance/instance_exception/TypeCastExceptionClassDeclare.h"
#include "trx/transaction_exception/DatabaseExceptionClassDeclare.h"

#include "base/UnicodeString.h"

namespace alinous {

ReservedClassRegistory::ReservedClassRegistory() {
	this->unit = new CompilationUnit();

	AnalyzedClass* aclass = StringClassDeclare::createAnalyzedClass();
	addAnalyzedClass(aclass);

	aclass = ExceptionClassDeclare::createAnalyzedClass();
	addAnalyzedClass(aclass);

	aclass = ArrayOutOfBoundsExceptionClassDeclare::createAnalyzedClass();
	addAnalyzedClass(aclass);

	aclass = NullPointerExceptionClassDeclare::createAnalyzedClass();
	addAnalyzedClass(aclass);

	aclass = ZeroDivisionExceptionClassDeclare::createAnalyzedClass();
	addAnalyzedClass(aclass);

	aclass = TypeCastExceptionClassDeclare::createAnalyzedClass();
	addAnalyzedClass(aclass);

	aclass = DatabaseExceptionClassDeclare::createAnalyzedClass();
	addAnalyzedClass(aclass);
}

AnalyzedClass* ReservedClassRegistory::getAnalyzedClass(const UnicodeString* fqn) const noexcept {
	return this->map.get(fqn);
}

void ReservedClassRegistory::addAnalyzedClass(AnalyzedClass* aclass) noexcept {
	aclass->setReserved(true);
	this->list.addElement(aclass);

	const UnicodeString* name = aclass->getFullQualifiedName();
	this->map.put(name, aclass);
}

ReservedClassRegistory::~ReservedClassRegistory() {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedClass* aclass = this->list.get(i);

		ClassDeclare* dec = aclass->getClassDeclare();
		delete dec;
	}

	this->list.deleteElements();

	delete this->unit;
}

const ArrayList<AnalyzedClass>* ReservedClassRegistory::getReservedClassesList() const noexcept {
	return &this->list;
}

CompilationUnit* ReservedClassRegistory::getUnit() const noexcept {
	return this->unit;
}


} /* namespace alinous */
