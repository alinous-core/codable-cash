/*
 * RangeScanner.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan/RangeChecker.h"

#include "table_record_key/AbstractCdbKey.h"

#include "btree/AbstractBtreeKey.h"

namespace codablecash {

RangeChecker::RangeChecker(const AbstractCdbKey* begin, bool beginEq, const AbstractCdbKey* end, bool endEq) {
	this->begin = begin->clone();
	this->beginEq = beginEq;
	this->end = end->clone();
	this->endEq = endEq;
}

RangeChecker::~RangeChecker() {
	delete this->begin;
	delete this->end;
}

AbstractBtreeKey* RangeChecker::getFirstScanKey() const noexcept {
	return this->begin;
}

bool RangeChecker::checkLower(const AbstractCdbKey* key) const noexcept {
	int result = this->begin->compareTo(key);

	return this->beginEq ? result >= 0 : result > 0;
}

bool RangeChecker::checkUpper(const AbstractCdbKey* key) const noexcept {
	int result = this->end->compareTo(key);

	return this->endEq ? result <= 0 : result < 0;
}


} /* namespace codablecash */
