/*
 * ReservedClassRegistory.cpp
 *
 *  Created on: 2020/03/16
 *      Author: iizuka
 */

#include "reserved_classes/ReservedClassRegistory.h"

#include "sc_analyze/AnalyzedClass.h"


namespace alinous {

ReservedClassRegistory::ReservedClassRegistory() {

}

ReservedClassRegistory* ReservedClassRegistory::getInstance() {
	static ReservedClassRegistory inst;

	return &inst;
}

ReservedClassRegistory::~ReservedClassRegistory() {
	this->list.deleteElements();
}

const ArrayList<AnalyzedClass>* ReservedClassRegistory::getReservedClassesList() const noexcept {
	return &this->list;
}

} /* namespace alinous */
