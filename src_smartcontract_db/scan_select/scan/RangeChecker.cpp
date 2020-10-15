/*
 * RangeScanner.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan_select/scan/RangeChecker.h"

#include "schema_table/record/table_record_key/AbstractCdbKey.h"
#include "schema_table/record/table_record_key/CdbRecordKey.h"

#include "btree/AbstractBtreeKey.h"


namespace codablecash {

RangeChecker::RangeChecker(const CdbRecordKey* begin, bool beginEq, const CdbRecordKey* end, bool endEq) {
	this->begin = begin != nullptr ? dynamic_cast<CdbRecordKey*>(begin->clone()) : nullptr;
	this->beginEq = beginEq;
	this->end = end != nullptr ? dynamic_cast<CdbRecordKey*>(end->clone()) : nullptr;
	this->endEq = endEq;
}

RangeChecker::~RangeChecker() {
	delete this->begin;
	delete this->end;
}

AbstractBtreeKey* RangeChecker::getFirstScanKey() const noexcept {
	return this->begin;
}

bool RangeChecker::checkLowerBound(const CdbRecordKey* key) const noexcept {
	if(this->begin == nullptr){
		return true;
	}

	int result = this->begin->compareTo(key);

	return this->beginEq ? result <= 0 : result < 0;
}

bool RangeChecker::checkUpperBound(const CdbRecordKey* key) const noexcept {
	if(this->end == nullptr){
		return true;
	}

	int result = this->end->compareTo(key);

	return this->endEq ? result >= 0 : result > 0;
}


} /* namespace codablecash */
