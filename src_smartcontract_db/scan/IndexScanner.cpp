/*
 * IndexScanner.cpp
 *
 *  Created on: 2020/06/04
 *      Author: iizuka
 */

#include "scan/IndexScanner.h"

#include "table_record_key/AbstractCdbKey.h"

namespace codablecash {

IndexScanner::IndexScanner(AbstractCdbKey* begin, bool beginEq, AbstractCdbKey* end, bool endEq) {
	this->begin = begin;
	this->beginEq = beginEq;
	this->end = end;
	this->endEq = endEq;

}

IndexScanner::~IndexScanner() {
	delete this->begin;
	delete this->end;
}

} /* namespace codablecash */
