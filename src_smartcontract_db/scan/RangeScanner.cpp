/*
 * RangeScanner.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan/RangeScanner.h"

#include "table_record_key/AbstractCdbKey.h"

#include "btree/AbstractBtreeKey.h"

namespace codablecash {

RangeScanner::RangeScanner(const AbstractCdbKey* begin, bool beginEq, const AbstractCdbKey* end, bool endEq) {
	this->begin = begin->clone();
	this->beginEq = beginEq;
	this->end = end->clone();
	this->endEq = endEq;
}

RangeScanner::~RangeScanner() {
	delete this->begin;
	delete this->end;
}

} /* namespace codablecash */
