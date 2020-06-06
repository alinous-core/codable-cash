/*
 * IndexScanner.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan/IndexScanner.h"

#include "table_record_key/AbstractCdbKey.h"

namespace codablecash {

IndexScanner::IndexScanner(AbstractCdbKey* begin, bool beginEq, AbstractCdbKey* end, bool endEq)
			: RangeScanner(begin, beginEq, end, endEq) {

}

IndexScanner::~IndexScanner() {

}

} /* namespace codablecash */
