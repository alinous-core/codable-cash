/*
 * ReservedClassRegistory.cpp
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#include "reserved_classes/ReservedClassRegistory.h"

#include "sc_analyze/AnalyzedClass.h"

#include "reserved_classes_string/StringClassDeclare.h"

#include "instance_exception_class/ExceptionClassDeclare.h"

namespace alinous {

ReservedClassRegistory::ReservedClassRegistory() {
	AnalyzedClass* aclass = StringClassDeclare::createAnalyzedClass();
	this->list.addElement(aclass);

	aclass = ExceptionClassDeclare::createAnalyzedClass();
	this->list.addElement(aclass);
}

ReservedClassRegistory* ReservedClassRegistory::getInstance() {
	static ReservedClassRegistory inst;

	return &inst;
}

ReservedClassRegistory::~ReservedClassRegistory() {
	int maxLoop = this->list.size();
	for(int i = 0; i != maxLoop; ++i){
		AnalyzedClass* aclass = this->list.get(i);

		ClassDeclare* dec = aclass->getClassDeclare();
		delete dec;
	}

	this->list.deleteElements();
}

const ArrayList<AnalyzedClass>* ReservedClassRegistory::getReservedClassesList() const noexcept {
	return &this->list;
}

} /* namespace alinous */
