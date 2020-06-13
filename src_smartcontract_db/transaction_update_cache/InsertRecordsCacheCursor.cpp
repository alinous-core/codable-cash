/*
 * InsertRecordsCacheCursor.cpp
 *
 *  Created on: 2020/06/13
 *      Author: iizuka
 */

#include "transaction_update_cache/InsertRecordsCacheCursor.h"

namespace codablecash {

InsertRecordsCacheCursor::InsertRecordsCacheCursor(const ArrayList<CdbRecord>* insertedRecords) {
	this->insertedRecords = insertedRecords;
	this->limit = insertedRecords->size();
	this->position = 0;
}

InsertRecordsCacheCursor::~InsertRecordsCacheCursor() {

}

bool InsertRecordsCacheCursor::hasNext() const noexcept {
	return this->position < this->limit;
}

const CdbRecord* InsertRecordsCacheCursor::next() noexcept {
	return this->insertedRecords->get(this->position++);
}

} /* namespace codablecash */
