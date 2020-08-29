/*
 * ScanResultMetadata.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "transaction_scan_result/ScanResultMetadata.h"
#include "transaction_scan_result/ScanResultFieldMetadata.h"

#include "base/UnicodeString.h"


namespace codablecash {


ScanResultMetadata::ScanResultMetadata(const ScanResultMetadata& inst) {
	this->list = new ArrayList<ScanResultFieldMetadata>();

	int maxLoop = inst.list->size();
	for(int i = 0; i != maxLoop; ++i){
		ScanResultFieldMetadata* fld = inst.list->get(i);

		addField(fld);
	}
}

ScanResultMetadata::ScanResultMetadata() {
	this->list = new ArrayList<ScanResultFieldMetadata>();
}


ScanResultMetadata::~ScanResultMetadata() {
	this->list->deleteElements();
	delete this->list;
}

void ScanResultMetadata::addField(const ScanResultFieldMetadata* fld) noexcept {
	ScanResultFieldMetadata* newFld = new ScanResultFieldMetadata(*fld);
	newFld->setPosition(this->list->size());

	this->list->addElement(newFld);
}

} /* namespace codablecash */

