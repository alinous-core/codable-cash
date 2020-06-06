/*
 * IndexScanner.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan/IndexScanner.h"

#include "table_record_key/AbstractCdbKey.h"

namespace codablecash {

IndexScanner::IndexScanner(AbstractCdbKey* begin, bool beginEq, AbstractCdbKey* end, bool endEq, IndexStore* store)
			: RangeScanner(begin, beginEq, end, endEq) {
	this->store = store;
}

IndexScanner::~IndexScanner() {

}

void IndexScanner::start() {

}

} /* namespace codablecash */
